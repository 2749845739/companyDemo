#include "GKeyBoard.h"

GKeyBoard::GKeyBoard(QDialog* parent):QDialog(parent)
  ,m_quickWidget(new QQuickWidget(this))
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground,true);
    QHBoxLayout* hLayout=new QHBoxLayout;
    hLayout->setMargin(0);
    setLayout(hLayout);
    hLayout->addWidget(m_quickWidget);
    this->setFixedSize(718,510);
    m_quickWidget->setSource(QUrl("qrc:/common/CusKeyboard.qml"));
    connect(m_quickWidget->rootObject(),SIGNAL(keyBoard(QVariant)),this,SLOT(slotGetKeyboard(QVariant)));
    connect(m_quickWidget->rootObject(),SIGNAL(keyBoardback()),this,SLOT(slotKeyBoardback()));
    connect(m_quickWidget->rootObject(),SIGNAL(keyBoardclose()),this,SLOT(slotKeyBoardclose()));
    //setModal(true);
}

void GKeyBoard::showKeyboard()
{
    QMetaObject::invokeMethod(m_quickWidget->rootObject(),"showKeyboard");
}

void GKeyBoard::slotGetKeyboard(QVariant value)
{
    emit sigKeyboard(value.toString());
}

void GKeyBoard::slotKeyBoardback()
{
    emit sigKeyBoardback();
}

void GKeyBoard::slotKeyBoardclose()
{
    //emit sigkeyBoardclose();
    QDialog::accept();
}
