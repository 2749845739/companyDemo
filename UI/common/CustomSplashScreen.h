#ifndef CUSTOMSPLASHSCREEN_H
#define CUSTOMSPLASHSCREEN_H
#include <QSplashScreen>
#include <QEvent>
#include <QMouseEvent>
class CustomSplashScreen:public QSplashScreen
{
    Q_OBJECT
public:
    explicit CustomSplashScreen(const QPixmap &pixmap);
    void mousePressEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void moveEvent(QMoveEvent *event) override;

};

#endif // CUSTOMSPLASHSCREEN_H
