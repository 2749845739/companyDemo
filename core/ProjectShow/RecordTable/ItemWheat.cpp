#include "ItemWheat.h"
#include <QDebug>
class ItemWheatPrivateDate{
public:
    QString m_sampleId   {""};
    QString m_gainName   {""};
    QString m_volumeweight   {""};
    QString m_unsound   {""};
    QString m_impurities   {""};
    QString m_moisture   {""};
    QString m_smell   {""};
    QString m_yzwheat   {""};
    QString m_qlweight   {""};
    QString m_jjwheat   {""};
    QString m_whitewhite   {""};
    QString m_createTime   {""};

    QString m_eaten    {""}; // 虫蚀
    QString m_mildew    {""}; // 生霉
    QString m_budding    {""}; // 生芽
    QString m_broken    {""}; // 破损
    QString m_scab    {""}; // 病斑
    QString m_gibberellic    {""}; // 赤霉
    QString m_blackEmbryo    {""}; // 黑胚

    int m_delegatetype   {0};
};
ItemWheat::ItemWheat(QObject *parent) : QObject(parent),m_P(new ItemWheatPrivateDate)
{

}

ItemWheat::ItemWheat(QStringList &data, QObject *parent):QObject(parent),m_P(new ItemWheatPrivateDate)
{
    m_P->m_createTime=data[0];
    m_P->m_sampleId=data[1];
    m_P->m_unsound=data[2];
    m_P->m_eaten=data[3];
    m_P->m_mildew=data[4];
    m_P->m_budding=data[5];
    m_P->m_broken=data[6];
    m_P->m_scab=data[7];
    m_P->m_gibberellic=data[8];
    m_P->m_blackEmbryo=data[9];
}

ItemWheat::~ItemWheat()
{

}

ItemWheat::ItemWheat(const ItemWheat &it)
{
    m_P=new ItemWheatPrivateDate;
    m_P->m_sampleId=it.m_P->m_sampleId;
    m_P->m_gainName=it.m_P->m_gainName;
    m_P->m_volumeweight=it.m_P->m_volumeweight;
    m_P->m_unsound=it.m_P->m_unsound;
    m_P->m_impurities=it.m_P->m_impurities;
    m_P->m_moisture=it.m_P->m_moisture;
    m_P->m_smell=it.m_P->m_smell;
    m_P->m_yzwheat=it.m_P->m_yzwheat;
    m_P->m_qlweight=it.m_P->m_qlweight;
    m_P->m_jjwheat=it.m_P->m_jjwheat;
    m_P->m_whitewhite=it.m_P->m_whitewhite;
    m_P->m_delegatetype=it.m_P->m_delegatetype;

    m_P->m_createTime=it.m_P->m_createTime;
    m_P->m_eaten=it.m_P->m_eaten;
    m_P->m_mildew=it.m_P->m_mildew;
    m_P->m_budding=it.m_P->m_budding;
    m_P->m_broken=it.m_P->m_broken;
    m_P->m_scab=it.m_P->m_scab;
    m_P->m_gibberellic=it.m_P->m_gibberellic;
    m_P->m_blackEmbryo=it.m_P->m_blackEmbryo;
}

ItemWheat &ItemWheat::operator=(const ItemWheat &other)
{
    m_P=new ItemWheatPrivateDate;
    m_P->m_sampleId=other.m_P->m_sampleId;
    m_P->m_gainName=other.m_P->m_gainName;
    m_P->m_volumeweight=other.m_P->m_volumeweight;
    m_P->m_unsound=other.m_P->m_unsound;
    m_P->m_impurities=other.m_P->m_impurities;
    m_P->m_moisture=other.m_P->m_moisture;
    m_P->m_smell=other.m_P->m_smell;
    m_P->m_yzwheat=other.m_P->m_yzwheat;
    m_P->m_qlweight=other.m_P->m_qlweight;
    m_P->m_jjwheat=other.m_P->m_jjwheat;
    m_P->m_whitewhite=other.m_P->m_whitewhite;
    m_P->m_delegatetype=other.m_P->m_delegatetype;

    m_P->m_createTime=other.m_P->m_createTime;
    m_P->m_eaten=other.m_P->m_eaten;
    m_P->m_mildew=other.m_P->m_mildew;
    m_P->m_budding=other.m_P->m_budding;
    m_P->m_broken=other.m_P->m_broken;
    m_P->m_scab=other.m_P->m_scab;
    m_P->m_gibberellic=other.m_P->m_gibberellic;
    m_P->m_blackEmbryo=other.m_P->m_blackEmbryo;
    return *this;
}

QString ItemWheat::sampleId()
{
    return m_P->m_sampleId;
}

void ItemWheat::setSampleId(QString value)
{
    m_P->m_sampleId=value;
    emit sampleIdChanged();
}

QString ItemWheat::gainName()
{
    return m_P->m_gainName;
}

void ItemWheat::setGainName(QString value)
{
    m_P->m_gainName=value;
    emit gainNameChanged();
}

QString ItemWheat::volumeweight()
{
    return m_P->m_volumeweight;
}

void ItemWheat::setVolumeweight(QString value)
{
    m_P->m_volumeweight=value;
    emit volumeweightChanged();
}

QString ItemWheat::unsound()
{
    return m_P->m_unsound;
}

void ItemWheat::setUnsound(QString value)
{
    m_P->m_unsound=value;
    emit unsoundChanged();
}

QString ItemWheat::impurities()
{
    return m_P->m_impurities;
}

void ItemWheat::setImpurities(QString value)
{
    m_P->m_impurities=value;
    emit impuritiesChanged();
}

QString ItemWheat::moisture()
{
    return m_P->m_moisture;
}

void ItemWheat::setMoisture(QString value)
{
    m_P->m_moisture=value;
    emit moistureChanged();
}

QString ItemWheat::smell()
{
    return m_P->m_smell;
}

void ItemWheat::setSmell(QString value)
{
    m_P->m_smell=value;
    emit smellChanged();
}

QString ItemWheat::yzwheat()
{
    return m_P->m_yzwheat;
}

void ItemWheat::setYzwheat(QString value)
{
    m_P->m_yzwheat=value;
    emit yzwheatChanged();
}

QString ItemWheat::qlweight()
{
    return m_P->m_qlweight;
}

void ItemWheat::setQlweight(QString value)
{
    m_P->m_qlweight=value;
    emit qlweightChanged();
}

QString ItemWheat::jjwheat()
{
    return m_P->m_jjwheat;
}

void ItemWheat::setJjwheat(QString value)
{
    m_P->m_jjwheat=value;
    emit jjwheatChanged();
}

int ItemWheat::delegateType()
{
    return m_P->m_delegatetype;
}

void ItemWheat::setDelegateType(int value)
{
    m_P->m_delegatetype=value;
    emit delegateTypeChanged();
}

QString ItemWheat::whitewhite()
{
    return m_P->m_whitewhite;
}

void ItemWheat::setWhitewhite(QString value)
{
    m_P->m_whitewhite=value;
    emit whitewhiteChanged();
}

QString ItemWheat::eaten()
{
    return m_P->m_eaten;
}

void ItemWheat::setEaten(QString value)
{
    m_P->m_eaten=value;
    emit eatenChanged();
}

QString ItemWheat::mildew()
{
    return m_P->m_mildew;
}

void ItemWheat::setMildew(QString value)
{
    m_P->m_mildew=value;
    emit mildewChanged();
}

QString ItemWheat::budding()
{
    return m_P->m_budding;
}

void ItemWheat::setBudding(QString value)
{
    m_P->m_budding=value;
    emit buddingChanged();
}

QString ItemWheat::broken()
{
    return m_P->m_broken;
}

void ItemWheat::setBroken(QString value)
{
    m_P->m_broken=value;
    emit brokenChanged();
}

QString ItemWheat::scab()
{
    return m_P->m_scab;
}

void ItemWheat::setScab(QString value)
{
    m_P->m_scab=value;
    emit scabChanged();
}

QString ItemWheat::gibberellic()
{
    return m_P->m_gibberellic;
}

void ItemWheat::setGibberellic(QString value)
{
    m_P->m_gibberellic=value;
    emit gibberellicChanged();
}

QString ItemWheat::blackEmbryo()
{
    return m_P->m_blackEmbryo;
}

void ItemWheat::setBlackEmbryo(QString value)
{
    m_P->m_blackEmbryo=value;
    emit blackEmbryoChanged();
}

QString ItemWheat::createTime()
{
    return m_P->m_createTime;
}

void ItemWheat::setCreateTime(QString value)
{
    m_P->m_createTime=value;
    emit createTimeChanged();
}

