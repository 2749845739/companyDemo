#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "FrameLessView.h"
#include "systemusagerate.h"
#include <QDebug>
#include <QQuickItem>
#include "RequireImage.h"
#include "gzcamera.h"
#include "../UI/Account/Login.h"
#include <QMovie>
#include <QSplashScreen>
#include <QThread>
#include <QLabel>
#include "boardcontrol.h"
#include "ManagerMath.h"
#include "RecordManager.h"
#include "dirver.h"
int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    Login login;
    if (login.exec() != QDialog::Accepted)
    {
        return 0;
    }
    QPixmap pixmap(":/Image/image/Login/loading.gif");
    QSplashScreen splash(pixmap);
    QMovie *Movie = new QMovie(":/Image/image/Login/loading.gif");
    QLabel  *Label = new QLabel(&splash);
    Label->setMovie(Movie);
    Movie->start();
    splash.show();
    app.processEvents();
//    for (int i = 0; i < 50; i++)
//    {
//        QCoreApplication::processEvents();
//        QThread::msleep(Movie->speed());
//    }
    qmlRegisterSingletonType(QUrl("qrc:/CusConfig.qml"),"chpan",1,0,"CusConfig");
//    SystemUsageRate sRate;
//    QObject::connect(&sRate,&SystemUsageRate::listRateChanged,[&](QList<int> info){
//        qDebug()<<info[0]<<"   "<<info[1];
//    });
    //sRate.start();
    //RequireImage requireImage(nullptr);

    //ManagerMath managerMath(nullptr);
    FrameLessView view;
//    GzCamera camera;
//    BoardControl boardControl;
#ifdef SOFTERTRIGER
//    QObject::connect(&boardControl,&BoardControl::sigUptrigger,&camera,&GzCamera::startCapture);
//    QObject::connect(&camera,&GzCamera::sigSetlightInfo,&boardControl,&BoardControl::setDownLight);
//    QObject::connect(&camera,&GzCamera::sigCloseDownLight,&boardControl,&BoardControl::closeDownLight);
#endif
//    QObject::connect(&boardControl,&BoardControl::sigWeight,&camera,&GzCamera::slotGetWeight);
//    QObject::connect(&boardControl,&BoardControl::sigWeight,camera.m_managerMath,&ManagerMath::getWeight,Qt::BlockingQueuedConnection);

//    QObject::connect(&boardControl,&BoardControl::sigUnsound,&camera,&GzCamera::slotUnsound);
//    QObject::connect(&boardControl,&BoardControl::sigAdjust,&camera,&GzCamera::slotAdjust);
//    QObject::connect(&boardControl,&BoardControl::sigAiAdjust,&camera,&GzCamera::slotAiAdjust);
//    //最后算法结果都是等板子的信号
//    QObject::connect(&boardControl,&BoardControl::finshDetection,camera.m_managerMath,&ManagerMath::dynamicResult);
//    //math judge send stop to board
//    QObject::connect(camera.m_managerMath,&ManagerMath::finshedDetect,&boardControl,&BoardControl::stopTask);
//    //notice qml
//    QObject::connect(camera.m_managerMath,&ManagerMath::dynamicFinshed,&boardControl,&BoardControl::finshedResult);
//    //send empty to board
//    QObject::connect(camera.m_managerMath,&ManagerMath::emptyGain,&boardControl,&BoardControl::sendGrainCount);

//    QObject::connect(camera.m_managerMath,&ManagerMath::sigGainType,&view,&FrameLessView::setcontext);
//    view.setMinimumSize({ 800, 600 });
//    view.resize(1024, 768);
//    view.rootContext()->setContextProperty("login", &login);
//    view.rootContext()->setContextProperty("boardControl", &boardControl);
//    view.rootContext()->setContextProperty("managerMath", camera.m_managerMath);
//    view.rootContext()->setContextProperty("mathModel", camera.m_managerMath->m_MathBaseModel.get());
//    view.rootContext()->setContextProperty("sRate", &sRate);
    view.rootContext()->setContextProperty("view", &view);
//    view.rootContext()->setContextProperty("camera", &camera);
//    view.rootContext()->setContextProperty("requireImageOne", camera.m_requireImageOne);
//    view.rootContext()->setContextProperty("requireImageTwo", camera.m_requireImageTwo);
//    view.engine()->addImageProvider("ViewProviderOne",camera.m_requireImageOne->multiView());
//    view.engine()->addImageProvider("ViewProviderTwo",camera.m_requireImageTwo->multiView());
//    view.engine()->addImageProvider("providerImg",camera.m_managerMath->m_providerImg);
//    qmlRegisterType<ItemWheat>       ("App.Class", 0, 1, "ItemWheat");
//    RecordManager recordManager;
//    QObject::connect(camera.m_managerMath,&ManagerMath::sigRecord,&recordManager,
//                     &RecordManager::addRecord);
//    view.rootContext()->setContextProperty("recordManager", &recordManager);
//    view.rootContext()->setContextProperty("recordWheatModel", recordManager.m_recordWheatModel);
//    view.rootContext()->setContextProperty("CurDirPath", QString(QApplication::applicationDirPath()));

    Dirver dirver;
    dirver.init();
    view.rootContext()->setContextProperty("flowControl",dirver.m_flowControl.get());
    view.rootContext()->setContextProperty("mainCamera",dirver.getRequireImg().get());
    view.rootContext()->setContextProperty("CameraProperty",dirver.getCameraProperty().get());
    const QUrl url("qrc:/main.qml");
    //qml call 'Qt.quit()' will emit engine::quit, here should call qApp->quit
    QObject::connect(view.engine(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);
    //qml clear content before quit
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, qApp, [&view](){view.setSource({});});

//    QVariantList list;
//    list << 10 << QColor(Qt::green) << "bottles";
    view.setSource(url);
    //view.moveToScreenCenter();
    view.showFullScreen();
    splash.finish(nullptr);
    return app.exec();
}
