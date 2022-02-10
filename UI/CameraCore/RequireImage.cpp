#include "RequireImage.h"
#include "ViewProvider.h"
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QDialog>
class RequireImagePrivate{
  public:
    RequireImagePrivate(){
    }
    void setCacheView(){
        m_multiView=new DisplaySegImgProvider;
    }
    void setSingleView(){
        m_multiView=new ViewProvider;
    }
    ViewProvider *m_multiView = nullptr;
};

RequireImage::RequireImage(QObject *parent):QObject(parent),d(new RequireImagePrivate)
{
    d->setSingleView();
}

QQuickImageProvider *RequireImage::multiView() const
{
    return d->m_multiView;
}

void RequireImage::getCameraImage(QImage &img)
{
    d->m_multiView->updateImage(m_index, img);
    emit viewNeedUpdate(m_index);
    if (++m_index == 16) m_index = 0;
}


UlightRequireImage::UlightRequireImage(QObject *parent):RequireImage(parent)
{
    d=new RequireImagePrivate;
    d->setSingleView();
}

void UlightRequireImage::getCameraImage(QImage & img)
{
    d->m_multiView->updateImage(m_index, img);
    emit viewNeedUpdate(m_index);
    if (++m_index == 4) m_index = 0;
}

SegGrainRequireImage::SegGrainRequireImage(QObject *parent):RequireImage(parent)
{
    d=new RequireImagePrivate;
    d->setCacheView();
}

void SegGrainRequireImage::getCameraImage(QImage img,int type)
{
    d->m_multiView->updateImage(m_index, img);
    emit segModelUpdate(m_index,type);
    if (++m_index == 80) m_index = 0;
}
