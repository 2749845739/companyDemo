#ifndef MANAGERMATH_H
#define MANAGERMATH_H
#include "TaskMath.h"
#include <QObject>
#include <QTimer>
#include <QDesktopServices>
#include "ViewProvider.h"
class ManagerMathPrivate;
class ManagerMath:public QObject
{
    Q_OBJECT

public:
    explicit ManagerMath(QObject* parent=nullptr);
    ~ManagerMath();

    void init();
    //qml
public slots:
    void initMathModel(int);
    void releaseModel();
    void processData(std::vector<im_data>);
    void dynamicResult();
    void savePng(std::vector<SaveImgData>,float weight);

    void clearImg();

    void timerStart();
    void timerStop();
    void prossDataTest();

    void getSegTypeImg(int type);

    void clearDir();
    void getWeight(float value);
    void openchm();
private:
    void getImgFormMath(QImage& img,int);
signals:
    void createHanderResult(bool flag);
    void releaseHanderResult(bool flag);

    void addImgtoView(int index,int grainType);
    void startGeiImage();
    void dynamicFinshed();

    void sigresultImg(QVariantList fileName);
    void finshedDetect();
    void emptyGain();

    void sigRecord(QStringList,QStringList,QStringList,QString);
    void sigGainType(GrainType,MathBaseModel*);
public:
    std::shared_ptr<MathBaseModel> m_MathBaseModel;
    std::shared_ptr<ParseMathDate> m_parseMathdate;
    std::shared_ptr<ConsumerImgData> m_consumerThread;
    std::shared_ptr<ProductionImgData> m_ProductThread;
    std::shared_ptr<BaseParameter> m_basePara;
    //test data
    std::vector<im_data> m_vec_data;
    im_data au_im_data;
    //////////
    QTimer * m_timer;
public:
    ViewProvider* m_providerImg;
    long long m_index   {0};
};

#endif // MANAGERMATH_H
