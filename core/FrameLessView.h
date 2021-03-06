#ifndef FRAMELESSVIEW_H
#define FRAMELESSVIEW_H
#include <QQuickView>
#include <GlobalParameter.h>
#include <QQmlContext>
#include "MathWheatModel.h"
//无边框窗口，主要用来实现自定义标题栏。
//Windows平台支持拖动和改变大小，支持Aero效果
//非Windows平台，去掉边框，不做其它处理。由Qml模拟resize和拖动。
class FrameLessViewPrivate;
class FrameLessView:public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(bool isMax READ isMax WRITE setIsMax NOTIFY isMaxChanged)
public:
    explicit FrameLessView(QWindow* parent=nullptr);
    ~FrameLessView();
    void moveToScreenCenter();
    bool isMax() const;
    QQuickItem *titleItem() const;
    static QRect calcCenterGeo(const QRect &screenGeo, const QSize &normalSize);
public slots:
    void setIsMax(bool isMax);
    void setTitleItem(QQuickItem *item);
    void setcontext(GrainType type,MathBaseModel* model);
signals:
    void isMaxChanged(bool isMax);
protected:
#    if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#    else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
#    endif
private:
    FrameLessViewPrivate *d;
};

#endif // FRAMELESSVIEW_H
