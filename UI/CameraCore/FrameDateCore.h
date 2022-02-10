/**
 * @file FrameDateCore.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FRAMEDATECORE_H
#define FRAMEDATECORE_H

#include <memory>

#include <QImage>
#include <QPainter>

#include "calibrate/calibrate.h"
#include "generator/dcdf_generator.h"
#include "module/camera/driver.h"
#include "module/camera/camera.h"
#include "module/camera/common.h"
#include "RequireImage.h"
#include "GlobalParameter.h"
#include "Gzlogger.h"

class FrameDateCore:public generator::dcdf_obs_frame {
 public:
    FrameDateCore();
    void handle_frame(generator::dcdf_frame frame) override;
    std::shared_ptr<RequireImage> m_requireImg;
};

class FlowCameraDateCore : public camera::camera_observer {
 public:
    explicit FlowCameraDateCore(int startLine = 0, int endLine = 0, int targetArea = 0);
    void handle_frame(camera::frame frame) override;
    void setparmeter(int startLine, int endLine, int targetArea);
    void setSaveImg();
    std::uint32_t getShowFramRate();
 public:
    std::shared_ptr<RequireImage> m_flowCameraRequireImg;
 private:
    int m_startLine;
    int m_endLine;
    int m_targetArea;
    bool m_isSaveImg  {false};
    std::uint32_t m_showFramRate  {0};
};

class MultilightCameraDateCore:public QObject, public calibrate::calibrate_obs {
    Q_OBJECT
 public:
    MultilightCameraDateCore();
    void calibrate_frame(calibrate::frame f) override;
    std::shared_ptr<RequireImage> m_lightCameraRequireImg;
    std::shared_ptr<RequireImage> m_inturnLightCameraRequireImg;
    void GrapImg();
    std::uint32_t getShowFramRate();
    bool m_isGrapImg {false};
    std::uint32_t m_showFramRate {0};

 signals:
    void sigsaveimg(bool);
};

#endif  // FRAMEDATECORE_H
