/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QDebug>
#include <QQuickItem>
#include <QMovie>
#include <QSplashScreen>
#include <QThread>
#include <QLabel>
#include <QDateTime>
#include <QSharedMemory>
#include "FrameLessView.h"
#include "CustomSplashScreen.h"
#include "RequireImage.h"
#include "UI/Account/Login.h"
#include "../TableModel/WheatItem.h"
#include "../TableModel/RecordWheatModel.h"
#include "UI/dirver/dirver.h"
#include "Gzlogger.h"
#include "logging/log.h"
#include "calibrate/calibrate.h"
#include "utils/utils.h"

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    // 初始化boost日志模块
    logging::logger::init(QString(QApplication::applicationDirPath()+"/logs").toStdString());
    // 设置控制板插件路径
    utils::common::instance()->set_board_plugin_path(
        QString(QApplication::applicationDirPath()+"/board_plugin").toStdString());
    // 设置相机插件路径
    utils::common::instance()->set_camera_plugin_path(
        QString(QApplication::applicationDirPath()+"/camera_plugin").toStdString());
    QSharedMemory shared("P600");
    if (shared.attach()) {
        return 0;
    }
    shared.create(1);

    app.setWindowIcon(QIcon(":/Image/image/user/icon.png"));
    Login login;
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }
    QPixmap pixmap(":/Image/image/Login/load.png");
    CustomSplashScreen splash(pixmap);
    splash.show();
    QThread::msleep(500);  // !!!键盘初始化 不然没有启动画面
    app.processEvents();
    qmlRegisterSingletonType(QUrl("qrc:/CusConfig.qml"), "chpan", 1, 0, "CusConfig");
    FrameLessView view;
    view.rootContext()->setContextProperty("view", &view);

    Dirver dirver;
    view.rootContext()->setContextProperty("dirver", &dirver);
    view.rootContext()->setContextProperty("Login", &login);
    view.rootContext()->setContextProperty("Logger", Logger::GetInstance());
    view.rootContext()->setContextProperty("GlobParameter", GlobalObject::g_instance());
    if (dirver.init()) {
        view.rootContext()->setContextProperty("flowControl",
            dirver.m_flowControl.get());

        view.rootContext()->setContextProperty("mainCamera",
            dirver.getRequireImg().get());

        view.rootContext()->setContextProperty("CameraProperty",
            dirver.getCameraProperty().get());

        view.rootContext()->setContextProperty("board",
            dirver.getBoardProperty().get());

        view.rootContext()->setContextProperty("CameraTaskWork",
            dirver.getCameraTaskWork().get());

        view.rootContext()->setContextProperty("flowCamera",
            dirver.getFlowCameraRequireImg().get());

        view.rootContext()->setContextProperty("lightView",
            dirver.getLightRequireImg().get());

        view.rootContext()->setContextProperty("lightViewProvider",
            dirver.getInturnLightRequireImg().get());

        view.engine()->addImageProvider("mainViewProvider",
            dirver.getRequireImg()->multiView());

        view.engine()->addImageProvider("flowViewProvider",
            dirver.getFlowCameraRequireImg()->multiView());

        view.engine()->addImageProvider("lightViewProvider",
            dirver.getLightRequireImg()->multiView());

        view.engine()->addImageProvider("inturnLightViewProvider",
            dirver.getInturnLightRequireImg()->multiView());

        view.rootContext()->setContextProperty("SegGrainRequireImage",
            dirver.getAlgorithmDataCore()->getSegGrainRequireImage());

        view.rootContext()->setContextProperty("ConsumerAlgorithmDataToUI",
            dirver.getAlgorithmDataCore()->getConsumerAlgorithmDataToUI());

        view.engine()->addImageProvider("SegImgprovider",
            dirver.getAlgorithmDataCore()->getSegGrainRequireImage()->multiView());

        QObject::connect(dirver.getAlgorithmDataCore().get(),
            &AlgorithmDataCore::sigAbstractAlgorithm,
            &view,
            &FrameLessView::setcontext);

        QObject::connect(&dirver,
            &Dirver::sigSqlSampleId,
            &view,
            &FrameLessView::setSqlcontext);
    }
    SqlWheatSampleId sqlSampleId;
    view.rootContext()->setContextProperty("sqlSampleId", &sqlSampleId);

    qmlRegisterUncreatableType<WheatItem>("App.Class", 0, 1, "WheatItem", "12");
    view.rootContext()->setContextProperty("WheatTabModel", sqlSampleId.m_recoedWheatModel);
    pixmap.load(":/Image/image/Login/loadFinshed.png");
    splash.setPixmap(pixmap);
    splash.show();
    app.processEvents();
    QThread::msleep(500);
    const QUrl url("qrc:/main.qml");
    QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, qApp, [&view](){
        view.setSource({});
    });
    view.setSource(url);
    view.showFullScreen();
    splash.finish(nullptr);
    return app.exec();
}
