#ifndef WHEATITEM_H
#define WHEATITEM_H
#include <memory>
#include <QObject>
#include <QMetaType>
class WheatItemPrivate;
class WheatItem: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sampleid READ sampleid WRITE setSampleid NOTIFY sampleidChanged)
    Q_PROPERTY(QString createTime READ createTime WRITE setCreateTime NOTIFY createTimeChanged)
    Q_PROPERTY(QString checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(QString mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(QString cs READ cs WRITE setCs NOTIFY csChanged)
    Q_PROPERTY(QString ps READ ps WRITE setPs NOTIFY psChanged)
    Q_PROPERTY(QString sy READ sy WRITE setSy NOTIFY syChanged)
    Q_PROPERTY(QString sm READ sm WRITE setSm NOTIFY smChanged)
    Q_PROPERTY(QString bb READ bb WRITE setBb NOTIFY bbChanged)
    Q_PROPERTY(QString cm READ cm WRITE setCm NOTIFY cmChanged)
    Q_PROPERTY(QString hp READ hp WRITE setHp NOTIFY hpChanged)
    Q_ENUMS(DelegateType)
public:
    QString sampleid();
    void setSampleid(QString value);

    QString createTime();
    void setCreateTime(QString value);

    QString checked();
    void setChecked(QString value);

    QString mass();
    void setMass(QString value);

    QString cs();
    void setCs(QString value);

    QString ps();
    void setPs(QString value);

    QString sy();
    void setSy(QString value);

    QString sm();
    void setSm(QString value);

    QString bb();
    void setBb(QString value);

    QString cm();
    void setCm(QString value);

    QString hp();
    void setHp(QString value);
signals:
    void sampleidChanged();
    void createTimeChanged();
    void checkedChanged();
    void massChanged();
    void csChanged();
    void psChanged();
    void syChanged();
    void smChanged();
    void bbChanged();
    void cmChanged();
    void hpChanged();
public:
    explicit WheatItem(QObject* parent=nullptr);
    explicit WheatItem(QStringList dataList,QObject* parent=nullptr);

    WheatItem(const WheatItem& item);

    WheatItem(WheatItem&& item);
    WheatItem& operator=(WheatItem&& item);
    WheatItem& operator=(const WheatItem& item);
    ~WheatItem();
public:
    enum DelegateType:unsigned int {TextEditor,CheckboxEditor};
    DelegateType delegateType();
    void setDelegateType(DelegateType value);
    QString indexData(int index);
private:
    std::shared_ptr<WheatItemPrivate> m_wheatItemPrivate;
    DelegateType m_delegateType;
};
Q_DECLARE_METATYPE(WheatItem)
#endif // WHEATITEM_H
