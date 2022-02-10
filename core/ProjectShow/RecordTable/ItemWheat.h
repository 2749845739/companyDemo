#ifndef ITEMWHEAT_H
#define ITEMWHEAT_H

#include <QObject>
class ItemWheatPrivateDate;
class ItemWheat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sampleId READ sampleId WRITE setSampleId NOTIFY sampleIdChanged)
    Q_PROPERTY(QString gainName READ gainName WRITE setGainName NOTIFY gainNameChanged)
    Q_PROPERTY(QString volumeweight READ volumeweight WRITE setVolumeweight NOTIFY volumeweightChanged)
    Q_PROPERTY(QString unsound READ unsound WRITE setUnsound NOTIFY unsoundChanged)
    Q_PROPERTY(QString impurities READ impurities WRITE setImpurities NOTIFY impuritiesChanged)
    Q_PROPERTY(QString moisture READ moisture WRITE setMoisture NOTIFY moistureChanged)
    Q_PROPERTY(QString smell READ smell WRITE setSmell NOTIFY smellChanged)
    Q_PROPERTY(QString yzwheat READ yzwheat WRITE setYzwheat NOTIFY yzwheatChanged)
    Q_PROPERTY(QString qlweight READ qlweight WRITE setQlweight NOTIFY qlweightChanged)
    Q_PROPERTY(QString jjwheat READ jjwheat WRITE setJjwheat NOTIFY jjwheatChanged)
    Q_PROPERTY(QString whitewhite READ whitewhite WRITE setWhitewhite NOTIFY whitewhiteChanged)
    Q_PROPERTY(int delegateType READ delegateType WRITE setDelegateType NOTIFY delegateTypeChanged)
    Q_PROPERTY(QString eaten READ eaten WRITE setEaten NOTIFY eatenChanged)
    Q_PROPERTY(QString mildew READ mildew WRITE setMildew NOTIFY mildewChanged)
    Q_PROPERTY(QString budding READ budding WRITE setBudding NOTIFY buddingChanged)
    Q_PROPERTY(QString broken READ broken WRITE setBroken NOTIFY brokenChanged)
    Q_PROPERTY(QString scab READ scab WRITE setScab NOTIFY scabChanged)
    Q_PROPERTY(QString gibberellic READ gibberellic WRITE setGibberellic NOTIFY gibberellicChanged)
    Q_PROPERTY(QString blackEmbryo READ blackEmbryo WRITE setBlackEmbryo NOTIFY blackEmbryoChanged)
    Q_PROPERTY(QString createTime READ createTime WRITE setCreateTime NOTIFY createTimeChanged)
    Q_ENUMS(FlagType)
    Q_ENUMS(DelegateType)
public:
    enum        FlagType {ReadOnly=1};
    enum       DelegateType {TextEditor,NumberEditor,BoolEditor,ColorEditor,ListEditor,PathEditor};
    explicit ItemWheat(QObject *parent = nullptr);
    explicit ItemWheat(QStringList& data,QObject *parent = nullptr);
    virtual ~ItemWheat();
    ItemWheat(const ItemWheat& it);
    ItemWheat &operator=(const ItemWheat &other);
    QString sampleId();
    void setSampleId(QString value);

    QString gainName();
    void setGainName(QString value);

    QString volumeweight();
    void setVolumeweight(QString value);

    QString unsound();
    void setUnsound(QString value);

    QString impurities();
    void setImpurities(QString value);

    QString moisture();
    void setMoisture(QString value);

    QString smell();
    void setSmell(QString value);

    QString yzwheat();
    void setYzwheat(QString value);

    QString qlweight();
    void setQlweight(QString value);

    QString jjwheat();
    void setJjwheat(QString value);

    int delegateType();
    void setDelegateType(int value);

    QString whitewhite();
    void setWhitewhite(QString value);

    QString eaten();
    void setEaten(QString value);

    QString mildew();
    void setMildew(QString value);

    QString budding();
    void setBudding(QString value);

    QString broken();
    void setBroken(QString value);

    QString scab();
    void setScab(QString value);

    QString gibberellic();
    void setGibberellic(QString value);

    QString blackEmbryo();
    void setBlackEmbryo(QString value);

    QString createTime();
    void setCreateTime(QString value);
signals:
    void sampleIdChanged();
    void gainNameChanged();
    void volumeweightChanged();
    void unsoundChanged();
    void impuritiesChanged();
    void moistureChanged();
    void smellChanged();
    void yzwheatChanged();
    void qlweightChanged();
    void jjwheatChanged();
    void delegateTypeChanged();
    void resultValueChanged();
    void whitewhiteChanged();
    void eatenChanged();
    void mildewChanged();
    void buddingChanged();
    void brokenChanged();
    void scabChanged();
    void gibberellicChanged();
    void blackEmbryoChanged();
    void createTimeChanged();
private:
    ItemWheatPrivateDate* m_P;
};
Q_DECLARE_METATYPE(ItemWheat)
#endif // ITEMWHEAT_H
