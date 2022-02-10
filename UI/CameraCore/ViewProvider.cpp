#include "ViewProvider.h"
#include <QDebug>
ViewProvider::ViewProvider(): QQuickImageProvider(QQuickImageProvider::Image)
{}
void ViewProvider::updateImage(int index,QImage view)
{
    //m_view[index]=view;
    m_img=view;
}
//qml 从这里拿
QImage ViewProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    //return m_view[id.toInt()];
    return m_img;
}

DisplaySegImgProvider::DisplaySegImgProvider()
{}

void DisplaySegImgProvider::updateImage(int index, QImage view)
{
    //save in mem
    //qDebug()<<"------------小图索引:"<<index<<"小图度:"<<view.width()<<"-----";
    m_view[index]=std::make_shared<QImage>(view.copy());
}

QImage DisplaySegImgProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    //m_view[id.toInt()].save(QString("/home/chpan/result/%1.png").arg(id),"PNG");
    if(m_view.contains(id.toInt())){
         return *m_view[id.toInt()];
    }else{
        return QImage();
    }
}
