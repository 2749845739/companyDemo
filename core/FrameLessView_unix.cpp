#include "FrameLessView.h"
#include <QScreen>
class FrameLessViewPrivate
{
public:
    bool m_isMax = false;
    QQuickItem *m_titleItem = nullptr;
};
FrameLessView::FrameLessView(QWindow* parent):QQuickView(parent),d(new FrameLessViewPrivate)
{
    setFlags(Qt::FramelessWindowHint);
    setResizeMode(SizeRootObjectToView);
    setIsMax(windowState()==Qt::WindowMaximized);
    connect(this,&QWindow::windowStateChanged,[this](Qt::WindowState state){
        setIsMax(state == Qt::WindowMaximized);
    });
}

FrameLessView::~FrameLessView()
{
    delete d;
}

void FrameLessView::moveToScreenCenter()
{
    auto geo=calcCenterGeo(screen()->availableGeometry(),size());
    if(minimumWidth()>geo.width()||minimumHeight()>geo.height()){
        setMinimumSize(geo.size());
    }
    setGeometry(geo);
    update();
}

bool FrameLessView::isMax() const
{
    return d->m_isMax;
}

QQuickItem *FrameLessView::titleItem() const
{
    return d->m_titleItem;
}

QRect FrameLessView::calcCenterGeo(const QRect &screenGeo, const QSize &normalSize)
{
    int w = normalSize.width();
    int h = normalSize.height();
    int x = screenGeo.x() + (screenGeo.width() - w) / 2;
    int y = screenGeo.y() + (screenGeo.height() - h) / 2;
    if (screenGeo.width() < w) {
        x = screenGeo.x();
        w = screenGeo.width();
    }
    if (screenGeo.height() < h) {
        y = screenGeo.y();
        h = screenGeo.height();
    }
    return { x, y, w, h };
}

void FrameLessView::setIsMax(bool isMax)
{
    if(d->m_isMax==isMax)
      return;
    d->m_isMax=isMax;
    emit isMaxChanged(d->m_isMax);
}

void FrameLessView::setTitleItem(QQuickItem *item)
{
    d->m_titleItem = item;
}

void FrameLessView::setcontext(GrainType type,MathBaseModel* model)
{
    //具体实例化哪个指标 expose qml
    switch (type) {
      case GrainType::WHEAT:
        rootContext()->setContextProperty("mathModel",qobject_cast<MathWheatModel*>(model));
        break;
      case GrainType::RICE:
    default:break;
    }


}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool TaoFrameLessView::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool FrameLessView::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif

{
    return QQuickView::nativeEvent(eventType, message, result);
}

