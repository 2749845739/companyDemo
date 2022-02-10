#include "WheatItem.h"
class WheatItemPrivate{
    public:
    QString m_checked {"false"};
    QString m_sampleId {""};
    QString m_createTime {""};
    QString m_mass {""};
    QString m_cs {""};
    QString m_ps {""};
    QString m_sy {""};
    QString m_sm {""};
    QString m_bb {""};
    QString m_cm {""};
    QString m_hp {""};
};

QString WheatItem::sampleid()
{
    return m_wheatItemPrivate->m_sampleId;
}

void WheatItem::setSampleid(QString value)
{
    m_wheatItemPrivate->m_sampleId=value;
    emit sampleidChanged();
}

QString WheatItem::createTime()
{
    return m_wheatItemPrivate->m_createTime;
}

void WheatItem::setCreateTime(QString value)
{
    m_wheatItemPrivate->m_createTime=value;
    emit createTimeChanged();
}

QString WheatItem::checked()
{
    return m_wheatItemPrivate->m_checked;
}

void WheatItem::setChecked(QString value)
{
    m_wheatItemPrivate->m_checked=value;
    emit checkedChanged();
}

QString WheatItem::mass()
{
    return m_wheatItemPrivate->m_mass;
}

void WheatItem::setMass(QString value)
{
    m_wheatItemPrivate->m_mass=value;
    emit massChanged();
}

QString WheatItem::cs()
{
    return m_wheatItemPrivate->m_cs;
}

void WheatItem::setCs(QString value)
{
    m_wheatItemPrivate->m_cs=value;
    emit csChanged();
}

QString WheatItem::ps()
{
    return m_wheatItemPrivate->m_ps;
}

void WheatItem::setPs(QString value)
{
    m_wheatItemPrivate->m_ps=value;
    emit psChanged();
}

QString WheatItem::sy()
{
    return m_wheatItemPrivate->m_sy;
}

void WheatItem::setSy(QString value)
{
    m_wheatItemPrivate->m_sy=value;
    emit syChanged();
}

QString WheatItem::sm()
{
    return m_wheatItemPrivate->m_sm;
}

void WheatItem::setSm(QString value)
{
    m_wheatItemPrivate->m_sm=value;
    emit smChanged();
}

QString WheatItem::bb()
{
    return m_wheatItemPrivate->m_bb;
}

void WheatItem::setBb(QString value)
{
    m_wheatItemPrivate->m_bb=value;
    emit bbChanged();
}

QString WheatItem::cm()
{
    return m_wheatItemPrivate->m_cm;
}

void WheatItem::setCm(QString value)
{
    m_wheatItemPrivate->m_cm=value;
    emit cmChanged();
}

QString WheatItem::hp()
{
    return m_wheatItemPrivate->m_hp;
}

void WheatItem::setHp(QString value)
{
    m_wheatItemPrivate->m_hp=value;
    emit hpChanged();
}

WheatItem::WheatItem(QObject* parent):QObject(parent),
    m_wheatItemPrivate(std::make_shared<WheatItemPrivate>())
{

}

WheatItem::WheatItem(QStringList dataList, QObject *parent):QObject(parent),
    m_wheatItemPrivate(std::make_shared<WheatItemPrivate>())
{
    setSampleid(dataList.at(0));
    setCreateTime(dataList.at(1));
    setMass(dataList.at(2));

    setSy(dataList.at(3));
    setCs(dataList.at(4));
    setPs(dataList.at(5));
    setSm(dataList.at(6));
    setBb(dataList.at(7));
    setCm(dataList.at(8));
    setHp(dataList.at(9));


    setDelegateType(DelegateType::TextEditor);
}

WheatItem::WheatItem(const WheatItem &item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
}

WheatItem::WheatItem(WheatItem &&item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
}

WheatItem &WheatItem::operator=(WheatItem &&item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
    return *this;
}

WheatItem &WheatItem::operator=(const WheatItem &item)
{
    m_wheatItemPrivate=item.m_wheatItemPrivate;
    m_delegateType=item.m_delegateType;
    return *this;
}

WheatItem::~WheatItem()
{

}

WheatItem::DelegateType WheatItem::delegateType()
{
    return m_delegateType;
}

void WheatItem::setDelegateType(DelegateType value)
{
    m_delegateType=value;
}

QString WheatItem::indexData(int index)
{
    QString value="";
    switch (index) {
    case 0:value=m_wheatItemPrivate->m_checked;
        break;
    case 1:value=m_wheatItemPrivate->m_sampleId;
        break;
    case 2:value=m_wheatItemPrivate->m_createTime;
        break;
    case 3:value=m_wheatItemPrivate->m_mass;
        break;
    case 4:value=m_wheatItemPrivate->m_cs;
        break;
    case 5:value=m_wheatItemPrivate->m_ps;
        break;
    case 6:value=m_wheatItemPrivate->m_sy;
        break;
    case 7:value=m_wheatItemPrivate->m_sm;
        break;
    case 8:value=m_wheatItemPrivate->m_bb;
        break;
    case 9:value=m_wheatItemPrivate->m_cm;
        break;
    case 10:value=m_wheatItemPrivate->m_hp;
        break;
    default:break;
    }
    return value;
}
