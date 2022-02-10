#ifndef REQUIREIMAGE_H
#define REQUIREIMAGE_H

#include <QObject>
#include <QQuickImageProvider>
class RequireImagePrivate;
class RequireImage:public QObject
{
    Q_OBJECT
public:
    explicit RequireImage(QObject* parent);

    QQuickImageProvider* multiView() const;
    virtual void getCameraImage(QImage&);
signals:
    void viewNeedUpdate(int index);
private:
    RequireImagePrivate* d;
    long long m_index   {0};
friend class UlightRequireImage;
friend class SegGrainRequireImage;
};

class UlightRequireImage: public RequireImage{
    Q_OBJECT
public:
    explicit UlightRequireImage(QObject* parent);
    void getCameraImage(QImage&) override;
};

class SegGrainRequireImage: public RequireImage{
    Q_OBJECT
public:
    explicit SegGrainRequireImage(QObject* parent);
public slots:
    void getCameraImage(QImage,int type);
signals:
    void segModelUpdate(int index,int type);
};
#endif // REQUIREIMAGE_H
