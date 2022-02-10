#include "AlgorithmWheat.h"
class GrainQuota:public QObject{
public:
    explicit GrainQuota(QObject* parent):QObject(parent){
    }
public:
    QVariantList m_shengya;
    QVariantList m_chongshi;
    QVariantList m_posun;
    QVariantList m_shengmei;
    QVariantList m_binban;
    QVariantList m_chimei;
    QVariantList m_heipei;
    QVariantList m_allRatio;
    QVariantList m_weightNormal;
};

QVariantList AlgorithmWheat::shengya()
{
    return m_grainQuota->m_shengya;
}

void AlgorithmWheat::setShengya(QVariantList value)
{
    m_grainQuota->m_shengya=value;
    emit shengyaChanged();
}

QVariantList AlgorithmWheat::chongshi()
{
    return m_grainQuota->m_chongshi;
}

void AlgorithmWheat::setChongshi(QVariantList value)
{
    m_grainQuota->m_chongshi=value;
    emit chongshiChanged();
}

QVariantList AlgorithmWheat::posun()
{
    return m_grainQuota->m_posun;
}

void AlgorithmWheat::setPosun(QVariantList value)
{
    m_grainQuota->m_posun=value;
    emit posunChanged();
}

QVariantList AlgorithmWheat::shengmei()
{
    return m_grainQuota->m_shengmei;
}

void AlgorithmWheat::setShengmei(QVariantList value)
{
    m_grainQuota->m_shengmei=value;
    emit shengmeiChanged();
}

QVariantList AlgorithmWheat::binban()
{
    return m_grainQuota->m_binban;
}

void AlgorithmWheat::setBinban(QVariantList value)
{
    m_grainQuota->m_binban=value;
    emit binbanChanged();
}

QVariantList AlgorithmWheat::chimei()
{
    return m_grainQuota->m_chimei;
}

void AlgorithmWheat::setChimei(QVariantList value)
{
    m_grainQuota->m_chimei=value;
    emit chimeiChanged();
}

QVariantList AlgorithmWheat::heipei()
{
    return m_grainQuota->m_heipei;
}

void AlgorithmWheat::setHeipei(QVariantList value)
{
    m_grainQuota->m_heipei=value;
    emit heipeiChanged();
}

QVariantList AlgorithmWheat::allRatio()
{
    return m_grainQuota->m_allRatio;
}

void AlgorithmWheat::setAllRatio(QVariantList value)
{
    m_grainQuota->m_allRatio=value;
    emit allRatioChanged();
}

QVariantList AlgorithmWheat::weightNormal()
{
    return m_grainQuota->m_weightNormal;
}

void AlgorithmWheat::setWeightNormal(QVariantList value)
{
    m_grainQuota->m_weightNormal=value;
    emit weightNormalChanged();
}

AlgorithmWheat::AlgorithmWheat(std::shared_ptr<AlgorithDataPool> dataPool,QObject*parent):
    m_dataPool(dataPool),AbstractAlgorithm(parent)
{
    m_grainQuota=new GrainQuota(this);
}

void AlgorithmWheat::porcess(algorithm::result& res)
{
    AlgorithmData data;
    data.recs=res.wheat.recs;
    for(int i=0;i<res.im_segment.size();i++){
        if(i>100) break;
        std::vector<std::shared_ptr<cv::Mat>> vecMat;
        for(int j=0;j<2;j++){
            vecMat.push_back(std::make_shared<cv::Mat>(
                                 res.im_segment.at(i).at(j)->clone()));
        }
        data.im_segment.push_back(vecMat);
    }
    LOGGER_DEBUG("处理显示小图");
    m_dataPool->process(data);
    //        for(int i=0;i<res.im_segment.size();i++){
    //            std::vector<std::shared_ptr<cv::Mat>> vecMatcopy;
    //            for(int j=0;j<2;j++){
    //                vecMatcopy.push_back(std::make_shared<cv::Mat>(
    //                                         res.im_segment.at(i).at(j)->clone()));
    //            }
    //            datacopy.im_segment.push_back(vecMatcopy);
    //        }
    //        WheatPicSort* picSort=new WheatPicSort(datacopy);
    //        QThreadPool::globalInstance()->start(picSort);
}

void AlgorithmWheat::dynamic_result(algorithm::result& res)
{
    m_weightRatio.clear();
    m_countRatio.clear();
    for(int i=0;i<res.wheat.wei_ratio.size();i++){
        LOGGER_DEBUG("质量比:%f",res.wheat.wei_ratio.at(i).second);
    }
    for(int i=0;i<res.wheat.count_ratio.size();i++){
        LOGGER_DEBUG("颗粒比:%f",res.wheat.count_ratio.at(i).second);
    }
    QVariantList vshengya;
    QVariantList vchongshi;
    QVariantList vposun;
    QVariantList vshengmei;
    QVariantList vbinban;
    QVariantList vchimei;
    QVariantList vheipei;
    QVariantList vallRatio;
    QVariantList vweightRatio;

    float cm , hpvalue;
    float mass=0.0;
    float particles=0.0;
    for(int i=0;i<res.wheat.wei_ratio.size();i++){
        switch (res.wheat.wei_ratio.at(i).first) {
        case algorithm::wheat_t::bb: {
            QString chimei=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            mass+=chimei.toFloat();
            cm=chimei.toFloat();
            vchimei.append(chimei);
            m_weightRatio<<chimei;
            break;
        }
        case algorithm::wheat_t::sy:
        {
            QString sy=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            vshengya.append(sy);
            mass+=sy.toFloat();
            m_weightRatio<<sy;
            break;
        }
        case algorithm::wheat_t::sm:
        {
            QString sm=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            vshengmei.append(sm);
            mass+=sm.toFloat();
            m_weightRatio<<sm;
            break;
        }
        case algorithm::wheat_t::cs:
        {
            QString cs=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            vchongshi.append(cs);
            mass+=cs.toFloat();
            m_weightRatio<<cs;
            break;
        }
        case algorithm::wheat_t::ps:
        {
            QString ps=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            vposun.append(ps);
            mass+=ps.toFloat();
            m_weightRatio<<ps;
            break;
        }
        case algorithm::wheat_t::hp:
        {
            QString hp=QString::number(res.wheat.wei_ratio.at(i).second*100,'f',2);
            vheipei.append(hp);
            mass+=hp.toFloat();
            hpvalue=hp.toFloat();
            m_weightRatio<<hp;
            break;
        }
        default:break;
        }
    }
    vbinban.append(QString::number(cm+hpvalue,'f',2));
    m_weightRatio<<QString::number(cm+hpvalue,'f',2);
    cm=0.0f;
    hpvalue=0.0f;
    for(int i=0;i<res.wheat.count_ratio.size();i++){
        switch (res.wheat.count_ratio.at(i).first) {
        case algorithm::wheat_t::bb: {
            QString chimei=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            particles+=chimei.toFloat();
            vchimei.append(chimei);
            cm=chimei.toFloat();
            m_countRatio<<chimei;
            break;
        }
        case algorithm::wheat_t::sy:
        {
            QString sy=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            vshengya.append(sy);
            particles+=sy.toFloat();
            m_countRatio<<sy;
            break;
        }
        case algorithm::wheat_t::sm:
        {
            QString sm=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            vshengmei.append(sm);
            particles+=sm.toFloat();
            m_countRatio<<sm;
            break;
        }
        case algorithm::wheat_t::cs:
        {
            QString cs=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            vchongshi.append(cs);
            particles+=cs.toFloat();
            m_countRatio<<cs;
            break;
        }
        case algorithm::wheat_t::ps:
        {
            QString ps=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            vposun.append(ps);
            particles+=ps.toFloat();
            m_countRatio<<ps;
            break;
        }
        case algorithm::wheat_t::hp:
        {
            QString hp=QString::number(res.wheat.count_ratio.at(i).second*100,'f',2);
            vheipei.append(hp);
            particles+=hp.toFloat();
            hpvalue=hp.toFloat();
            m_countRatio<<hp;
            break;
        }
        default:break;
        }
    }
    vbinban.append(QString::number(cm+hpvalue,'f',2));
    m_countRatio<<QString::number(cm+hpvalue,'f',2);
    if(mass>100.00) mass=100.00f;
    if(particles>100.00) particles=100.00f;
    m_mass=QString::number(mass,'f',2);
    m_particles=QString::number(particles,'f',2);
    vallRatio.append(m_mass);
    vallRatio.append(m_particles);

    vweightRatio.append(100.0-mass);
    vweightRatio.append(QString::number(100.0-mass,'f',2));
    setWeightNormal(vweightRatio);
    setShengya(vshengya);
    setChongshi(vchongshi);
    setPosun(vposun);
    setShengmei(vshengmei);
    setBinban(vbinban);
    setChimei(vchimei);
    setHeipei(vheipei);
    setAllRatio(vallRatio);
    emit sigDynamicFinshed();
}

bool AlgorithmWheat::printResult()
{
    QString pLogo = QString("\n        高哲AI快检仪       ");
    QString dev = printDev();
    QString pSplitLine = QString("\n------------------------------");
    QString smapleId=QString("样品编号:%1").arg(GlobalObject::g_sampleId);
    QString detectionTime=QString("检测时间:%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QString quato=QString("    指标  质量比  颗粒比\n    不完善粒  %1%  %2%\n    生芽粒    %3%  %4%\n    虫蚀粒    %5%  %6%\n    破损粒    %7%  %8%\n    生霉粒    %9%  %10%\n    病斑粒    %11%  %12%\n    赤霉粒    %13%  %14%\n    黑胚粒    %15%  %16%\n")
            .arg(m_mass).arg(m_particles)
            .arg(m_weightRatio.at(1)).arg(m_countRatio.at(1)).arg(m_weightRatio.at(3)).arg(m_countRatio.at(3))
            .arg(m_weightRatio.at(4)).arg(m_countRatio.at(4)).arg(m_weightRatio.at(2)).arg(m_countRatio.at(2))
            .arg(binban().at(0).toString()).arg(binban().at(1).toString())
            .arg(m_weightRatio.at(0)).arg(m_countRatio.at(0)).arg(m_weightRatio.at(5)).arg(m_countRatio.at(5));
    if(!dev.isEmpty())
    {
        QString printV;
        printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pLogo).arg(dev);
        printVal(printV.toUtf8());
        printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(smapleId).arg(dev);
        printVal(printV.toUtf8());
        printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(detectionTime).arg(dev);
        printVal(printV.toUtf8());
        printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(quato).arg(dev);
        printVal(printV.toUtf8());
        printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pSplitLine).arg(dev);
        printVal(printV.toUtf8());
        return true;
    }else {
        return false;
    }
}

void AlgorithmWheat::getSegTypeImg(int type)
{
    QString dirName="";
    switch (type) {
    case 0:break;
    case 1:dirName ="1/";break;
    case 2:dirName ="2/";break;
    case 3:dirName ="3/";break;
    case 4:dirName ="4/";break;
    case 5:dirName ="5/";break;
    case 6:dirName ="6/";break;
    case 7:dirName ="7/";break;
    case 10:dirName ="-1";break;
    default:break;
    }
    QVariantList fileName;
    if(dirName=="-1"){
        for(int i=1;i<7;i++){
            QDir dir(QApplication::applicationDirPath()+"/segResult/"+QString::number(i)+"/");
            QFileInfoList fileList=dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files,QDir::Time);
            for(auto &it:fileList){
                fileName.append(it.absoluteFilePath());
            }
        }
    }else{
        QDir dir(QApplication::applicationDirPath()+"/segResult/"+dirName);
        QFileInfoList fileList=dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files,QDir::Time);
        for(auto &it:fileList){
            fileName.append(it.absoluteFilePath());
        }
    }

    emit sigMergeImg(fileName);
}

AlgorithmWheatTypeFactor::AlgorithmWheatTypeFactor
(std::shared_ptr<AlgorithDataPool> dataPool):m_dataPool(dataPool)
{}

std::shared_ptr<AbstractAlgorithm> AlgorithmWheatTypeFactor::createAlgorithm()
{
    return std::make_shared<AlgorithmWheat>(m_dataPool);
}

WheatPicSort::WheatPicSort(AlgorithmData data):m_data(data)
{}
std::atomic<std::uint64_t> g_imgCout  {0};
void WheatPicSort::run()
{
    int num = 0;
    for(auto &it:m_data.im_segment){
        QString dirname="";
        int type = static_cast<int>(m_data.recs.at(num).first);
        switch (type){
        case 0: break;
        case 1: dirname="1/";break;
        case 2: dirname="2/";break;
        case 3: dirname="3/";break;
        case 4: dirname="4/";break;
        case 5: dirname="5/";break;
        case 6: dirname="6/";break;
        default: qDebug() << "[TASKMATH-ERROR] save image failed"; break;
        }
        num++;
        if(dirname==""){
            continue;
        }
        cv::Mat image_one=*it[0];
        cv::Mat image_two=*it[1];
        cv::Mat result = cv::Mat::zeros(cv::Size(image_one.cols * 2, image_one.rows), CV_8UC3);

        image_one.copyTo(result(cv::Rect(0, 0, image_one.cols, image_one.rows)));
        image_two.copyTo(result(cv::Rect(image_two.cols, 0, image_two.cols, image_two.rows)));
        QString imgName= QApplication::applicationDirPath()+"/segResult/"+dirname+ QString::number(g_imgCout++)+".png";
        QByteArray b1=imgName.toLatin1();
        cv::imwrite(b1.data(),result);
        if(dirname=="1/"||dirname=="6/"){
            QString imgName= QApplication::applicationDirPath()+"/segResult/"+"7/"+ QString::number(g_imgCout++)+".png";
            QByteArray b1=imgName.toLatin1();
            cv::imwrite(b1.data(),result);
        }
    }
}
