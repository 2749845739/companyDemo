/**
 * @file dirver.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UI_DIRVER_DIRVER_H_
#define UI_DIRVER_DIRVER_H_

#include <memory>
#include <QObject>
#include "generator/dcdf_generator.h"
#include "../BoardCore/BoardInterface.h"
#include "../CameraCore/CameraInterface.h"
#include "FlowControl.h"
#include "CameraTaskWork.h"
#include "../AlgorithmCore/AlgorithmManager.h"
#include "../AlgorithmCore/AlgorithmDataCore.h"
#include "module/def.h"
#include "Login.h"
#include "../../algorithm/im_saving/dcdf_save.h"
#include "SqlSampleId.h"
class Dirver:public QObject {
    Q_OBJECT

 public:
    Dirver();
    bool init();
    inline std::shared_ptr<RequireImage> getRequireImg() {
        return m_dateCore->m_requireImg;
    }
    inline std::shared_ptr<RequireImage> getFlowCameraRequireImg() {
        if(m_flowCameraDateCorel)
        return m_flowCameraDateCorel->m_flowCameraRequireImg;
        else return nullptr;
    }
    inline std::shared_ptr<RequireImage> getLightRequireImg() {
        if(m_cameraTaskWork)
        return m_cameraTaskWork->m_MultilightCameraDateCore->m_lightCameraRequireImg;
        else return nullptr;
    }
    inline std::shared_ptr<RequireImage> getInturnLightRequireImg() {
        if(m_cameraTaskWork)
        return m_cameraTaskWork->m_MultilightCameraDateCore->m_inturnLightCameraRequireImg;
        else return nullptr;
    }
    inline std::shared_ptr<CameraProperty> getCameraProperty() {
        if(m_cameraInterface)
        return m_cameraInterface->m_cameraProperty;
        else return nullptr;
    }
    inline std::shared_ptr<BoardProperty> getBoardProperty() {
        if(m_cameraInterface)
        return m_boardInterface->m_boardProperty;
        else return nullptr;
    }
    inline std::shared_ptr<CameraTaskWork> getCameraTaskWork() {
        return m_cameraTaskWork;
    }
    inline std::shared_ptr<AlgorithmDataCore> getAlgorithmDataCore(){
        if(m_algorithmDataCore)
        return m_algorithmDataCore;
        else return nullptr;
    }
 public:
    Q_INVOKABLE void initAllParamter();
    Q_INVOKABLE void dcdfStart();
    Q_INVOKABLE void dcdfStop();
 private slots:
    void slotSetCameraBright(QString, int);
    void slotSetCameraDark(QString, int);
    void slotSaveImgEnable(bool);
 signals:
    void sigSqlSampleId(SqlSampleId*);
 public:
    std::shared_ptr<generator::dcdf_engine> m_dcdfCore;
    std::shared_ptr<CameraInterface> m_cameraInterface;
    std::shared_ptr<BoardInterface> m_boardInterface;
    std::shared_ptr<FrameDateCore> m_dateCore;
    std::shared_ptr<FlowControl> m_flowControl;
    std::shared_ptr<FlowCameraDateCore> m_flowCameraDateCorel;
    std::shared_ptr<CameraTaskWork> m_cameraTaskWork;

    std::shared_ptr<AlgorithmManager> m_algorithmManager;
    std::shared_ptr<AlgorithmDataCore> m_algorithmDataCore;
    std::shared_ptr<algorithm::dcdf_save> m_dcdfSave;
    //SqlSampleId* m_sqlSampleId;
};

#endif  // UI_DIRVER_DIRVER_H_
