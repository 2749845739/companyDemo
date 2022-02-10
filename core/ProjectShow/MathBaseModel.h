#ifndef MATHMODEL_H
#define MATHMODEL_H
#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QTime>
#include <GlobalParameter.h>
#include "gz_graineval_api.h"
#include <queue>
#include <mutex>
#include <QThread>
#include <QThreadPool>
#include <QImage>
#include <QMetaType>
#include <opencv2/opencv.hpp>

using CVImagData = std::vector<std::vector<std::shared_ptr<cv::Mat>>>;
using im_data=std::shared_ptr<cv::Mat>;
using WheatGraintype = std::vector<std::pair<wheat_t, float>>;
using RiceGraintype = std::vector<std::pair<rice_t, float>>;
struct imgDataStruct{
    CVImagData imgData;
    //WHEAT
    WheatGraintype wheatType;
    //RICE
    RiceGraintype riceType;
    //CORN
};
class BaseParameter :public QObject{
    Q_OBJECT
public:
    explicit BaseParameter();
    BaseParameter(const BaseParameter& )=delete;
public:
    // 算法参数
    GZ_HANDLE handler;
    GrainType m_grainType;
    GZ_GrainEval_Result_S m_result;
    sbatch_data m_input_data;

    // 处理参数
    std::queue<GZ_GrainEval_Result_S>  m_queue;
    std::mutex m_mutex;
    std::mutex m_mutex_img;
    std::condition_variable cond;
    std::condition_variable condImg_notfull;
    std::condition_variable condImg_notempty;
    std::queue<imgDataStruct> m_queueImg;
};

class MathBaseModel :public QObject{
    Q_OBJECT
public:
    explicit MathBaseModel(std::shared_ptr<BaseParameter>);
    //最后指标
    virtual QVector<QStringList> setQuota(){
        return QVector<QStringList>();
    }
    virtual QString setGrainType() { return ""; }
    //实时指标
    virtual void realShowQuota(GZ_GrainEval_Result_S&){
    }
    //分割分类结果
    virtual void setSegtype(imgDataStruct&,GZ_GrainEval_Result_S&);
    //
    virtual int  getSegtype(imgDataStruct&,int){return 0;}
public:
    std::shared_ptr<BaseParameter> m_base;
};
#endif // MATHMODEL_H
