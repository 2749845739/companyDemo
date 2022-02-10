#ifndef VIEWPROVIDER_H
#define VIEWPROVIDER_H
#include <QQuickImageProvider>

class ViewProvider:public QQuickImageProvider
{
public:
    explicit ViewProvider();

    virtual void updateImage(int index,QImage view);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
public:
    QMap<int,std::shared_ptr<QImage>> m_view;
    QImage m_img;
};

class DisplaySegImgProvider:public ViewProvider {
public:
    explicit DisplaySegImgProvider();
    void updateImage(int index,QImage view) override;
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // VIEWPROVIDER_H
