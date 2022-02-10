#include "CustomSplashScreen.h"

CustomSplashScreen::CustomSplashScreen(const QPixmap &pixmap):QSplashScreen(pixmap)
{

}
void CustomSplashScreen::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void CustomSplashScreen::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->ignore();
}

void CustomSplashScreen::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}

void CustomSplashScreen::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void CustomSplashScreen::moveEvent(QMoveEvent *event)
{
    event->ignore();
}
