#ifndef TASKMATH_H
#define TASKMATH_H

#include "MathWheatModel.h"
class TaskMath:public QObject, public QRunnable
{
    Q_OBJECT
public:
    using func=std::function<void()>;
    explicit TaskMath(std::shared_ptr<MathBaseModel>);
    void run();
    void setCallBack(func p);
public:
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
    func f;
};

class TaskCreateHandler :public TaskMath{
     Q_OBJECT
public:
    explicit TaskCreateHandler(std::shared_ptr<MathBaseModel> m);
signals:
    void GrainEval_Create_Status(bool);

};
class TaskReleaseHandler :public TaskMath{
     Q_OBJECT
public:
    explicit TaskReleaseHandler(std::shared_ptr<MathBaseModel> m);
signals:
    void GrainEval_Release_Status(bool);

};

class TaskProcess :public TaskMath{
     Q_OBJECT
public:
    explicit TaskProcess(std::shared_ptr<MathBaseModel> m);
signals:
    void finshedDetect();
    //void processData(processResult);
    void detectEmptyGrain();
public:
};
class TaskSavePic:public QRunnable{
public:
    TaskSavePic(std::vector<SaveImgData> data,std::shared_ptr<MathBaseModel> MathBaseModel, float value);
    void run() override;
private:
    std::vector<SaveImgData> m_imgData;
    //QStringList m_imgName;
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
    float m_weight;
};

class TaskDynamicResult :public TaskMath{
     Q_OBJECT
public:
    explicit TaskDynamicResult(std::shared_ptr<MathBaseModel> m);
signals:
    void GrainEval_finshed();
    void sigResult(QStringList,QStringList,QStringList,QString grainName);
public:
};

class ParseMathDate :public QThread{
    Q_OBJECT
public:
    explicit ParseMathDate(std::shared_ptr<MathBaseModel>);
    explicit ParseMathDate();
    void setM_MathBaseModel(std::shared_ptr<MathBaseModel>);
    void run() override;
    void stopThread();
signals:
    void sigImg();
    void sigpushImg(imgDataStruct);
private:
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
    bool m_stop;
};

class TaskPushImgData:public TaskMath{
    Q_OBJECT
public:
    TaskPushImgData(std::shared_ptr<MathBaseModel>,imgDataStruct);
private:
    imgDataStruct m_data;
};

class ProductionImgData:public QObject{
    Q_OBJECT
public:
    explicit ProductionImgData(std::shared_ptr<MathBaseModel>);
public slots:
    void push_back(imgDataStruct);
private:
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
};
class ConsumerImgData :public QThread{
    Q_OBJECT
public:
    explicit ConsumerImgData(std::shared_ptr<MathBaseModel>);
    void run() override;
    void stopThread();
    void saveSegpng(imgDataStruct& imgs);
    void setM_MathBaseModel(std::shared_ptr<MathBaseModel>);
signals:
    void sigtoShow(QImage&,int);
    void finshedOne();
private:
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
    bool m_stop;
};

#endif // TASKMATH_H
