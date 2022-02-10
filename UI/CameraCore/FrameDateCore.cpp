/**
 * @file FrameDateCore.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <memory>
#include "FrameDateCore.h"
#include "QByteArray"

QImage converToImage(unsigned char* data, int w, int h) {
    BGR2RGB(data, w, h);
    return QImage(data, w, h, w*3, QImage::Format_RGB888, 0, 0).copy();
}

FrameDateCore::FrameDateCore() : m_requireImg(std::make_shared<RequireImage>(nullptr)) {}

void FrameDateCore::handle_frame(generator::dcdf_frame frame) {
    LOGGER_DEBUG("FrameDateCore callback");
    std::shared_ptr<cv::Mat> pua = std::make_shared<cv::Mat>(
      cv::Mat(frame.ua->h, frame.ua->w, CV_8UC3, frame.ua->data.get()).clone());

    QImage ui_ua = converToImage(pua.get()->data, pua->cols, pua->rows);
    m_requireImg->getCameraImage(ui_ua);

    std::shared_ptr<cv::Mat> pub = std::make_shared<cv::Mat>(
      cv::Mat(frame.ub->h, frame.ub->w, CV_8UC3, frame.ub->data.get()).clone());
    QImage ui_ub = converToImage(pub.get()->data, pub->cols, pub->rows);
    m_requireImg->getCameraImage(ui_ub);

    std::shared_ptr<cv::Mat> pda = std::make_shared<cv::Mat>(
      cv::Mat(frame.da->h, frame.da->w, CV_8UC3, frame.da->data.get()).clone());
    QImage ui_da = converToImage(pda.get()->data, pda->cols, pda->rows);
    m_requireImg->getCameraImage(ui_da);

    std::shared_ptr<cv::Mat> pdb = std::make_shared<cv::Mat>(
      cv::Mat(frame.db->h, frame.db->w, CV_8UC3, frame.db->data.get()).clone());
    QImage ui_db = converToImage(pdb.get()->data, pdb->cols, pdb->rows);
    m_requireImg->getCameraImage(ui_db);
}

FlowCameraDateCore::FlowCameraDateCore(int startLine, int endLine, int targetArea)
        : m_startLine(startLine), m_endLine(endLine), m_targetArea(targetArea) {
    m_flowCameraRequireImg = std::make_shared<RequireImage>(nullptr);
    QDir dir(QApplication::applicationDirPath());
    dir.mkdir("flowImg");
    dir.mkdir("flowmodel");
    dir.mkdir("grapImg");
}

void FlowCameraDateCore::handle_frame(camera::frame frame) {
    std::shared_ptr<cv::Mat> pfc = std::make_shared<cv::Mat>(
      cv::Mat(frame.h, frame.w, CV_8UC3, frame.data.get()).clone());
    QImage ui = converToImage(pfc.get()->data, pfc->cols, pfc->rows);
    QPixmap pix = QPixmap::fromImage(ui);
    if (m_isSaveImg) {
        pix.save(QString(QApplication::applicationDirPath()+"/flowImg/fc_template.png"));
        m_isSaveImg = !m_isSaveImg;
    }
    QPainter painter(&pix);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawLine(m_startLine, 0, m_startLine, ui.height());

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(m_startLine+m_targetArea, 0, m_startLine+m_targetArea, ui.height());

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(m_endLine, 0, m_endLine, ui.height());

    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(m_endLine-m_targetArea, 0, m_endLine-m_targetArea, ui.height());

    QImage img = pix.toImage();
    m_flowCameraRequireImg->getCameraImage(img);
    m_showFramRate++;
}

void FlowCameraDateCore::setparmeter(int startLine, int endLine, int targetArea) {
    m_startLine = startLine;
    m_endLine = endLine;
    m_targetArea = targetArea;
}

void FlowCameraDateCore::setSaveImg() {
    m_isSaveImg = true;
}

uint32_t FlowCameraDateCore::getShowFramRate() {
    return m_showFramRate;
}

MultilightCameraDateCore::MultilightCameraDateCore():
    m_lightCameraRequireImg(std::make_shared<UlightRequireImage>(nullptr)),
    m_inturnLightCameraRequireImg(std::make_shared<RequireImage>(nullptr))
{}

void MultilightCameraDateCore::calibrate_frame(calibrate::frame frame) {
    m_showFramRate++;
    bool is_inturn = false;
    if (frame.s == calibrate::state::inturn_acquire ||
        frame.s == calibrate::state::dcdf_acquire) {
        is_inturn = true;
    }

    QImage ui_ua, ui_ub, ui_da, ui_db;
    if (frame.ua) {
        std::shared_ptr<cv::Mat> pua = std::make_shared<cv::Mat>(
            cv::Mat(frame.ua->h, frame.ua->w, CV_8UC3, frame.ua->data.get()).clone());
        ui_ua = converToImage(pua.get()->data, pua->cols, pua->rows);
        if (is_inturn) {
            m_inturnLightCameraRequireImg->getCameraImage(ui_ua);
        } else {
            m_lightCameraRequireImg->getCameraImage(ui_ua);
        }
    }

    if (frame.ub) {
        std::shared_ptr<cv::Mat> pub = std::make_shared<cv::Mat>(
            cv::Mat(frame.ub->h, frame.ub->w, CV_8UC3, frame.ub->data.get()).clone());
        ui_ub = converToImage(pub.get()->data, pub->cols, pub->rows);
        if (is_inturn) {
            m_inturnLightCameraRequireImg->getCameraImage(ui_ub);
        } else {
            m_lightCameraRequireImg->getCameraImage(ui_ub);
        }
    }

    if (frame.da) {
        std::shared_ptr<cv::Mat> pda = std::make_shared<cv::Mat>(
            cv::Mat(frame.da->h, frame.da->w, CV_8UC3, frame.da->data.get()).clone());
        ui_da = converToImage(pda.get()->data, pda->cols, pda->rows);
        if (is_inturn) {
            m_inturnLightCameraRequireImg->getCameraImage(ui_da);
        } else {
            m_lightCameraRequireImg->getCameraImage(ui_da);
        }
    }

    if (frame.db) {
        std::shared_ptr<cv::Mat> pdb = std::make_shared<cv::Mat>(
            cv::Mat(frame.db->h, frame.db->w, CV_8UC3, frame.db->data.get()).clone());
        ui_db = converToImage(pdb.get()->data, pdb->cols, pdb->rows);
        if (is_inturn) {
            m_inturnLightCameraRequireImg->getCameraImage(ui_db);
        } else {
            m_lightCameraRequireImg->getCameraImage(ui_db);
        }
    }

    if (m_isGrapImg) {
        QList<QImage> save_list;
        if (is_inturn) {
            save_list.append({ui_ua, ui_ub, ui_da, ui_db});
        } else if (frame.s == calibrate::state::ulight_acquire) {
            save_list.append({ui_ua, ui_db});
        } else {
            save_list.append({ui_ub, ui_da});
        }
        SavePng *task = new SavePng(save_list);
        connect(task, &SavePng::sigfinshed, this, &MultilightCameraDateCore::sigsaveimg);
        QThreadPool::globalInstance()->start(task);
        m_isGrapImg = !m_isGrapImg;
    }
}

void MultilightCameraDateCore::GrapImg() {
    m_isGrapImg = true;
}

std::uint32_t MultilightCameraDateCore::getShowFramRate() {
    return m_showFramRate;
}
