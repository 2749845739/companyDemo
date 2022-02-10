#include "CMessageBox.h"
#include "ui_CMessageBox.h"
#include<QStyle>
#include<QDebug>

CMessageBox::CMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMessageBox)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    ui->labelclose->installEventFilter(this);
    ui->btnCancel->setProperty("style","white");
    ui->btnCancel->style()->unpolish(ui->btnCancel);
    ui->btnCancel->style()->polish(ui->btnCancel);
}

CMessageBox::~CMessageBox()
{
    delete ui;
}


int CMessageBox::setInfo(const QString info, CMessageBox::StandardButton standardButton)
{
    ui->labelmsg->setText(info);
    switch (standardButton) {
    case StandardButton::OK:
        ui->btnOk->setVisible(true);
        ui->btnOk->setText(tr("确定"));
        ui->btnCancel->setVisible(false);
        break;
    case StandardButton::YesNo:
        ui->btnOk->setVisible(true);
        ui->btnOk->setText(tr("是"));
        ui->btnCancel->setVisible(true);
        ui->btnCancel->setText(tr("否"));
        break;
    }
    ui->btnOk->setFocus();
    this->setModal(true);
    return this->exec();
}

void CMessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void CMessageBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void CMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}

bool CMessageBox::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->labelclose)//指定某个QLabel
        {
            if (event->type() == QEvent::MouseButtonPress)//mouse button pressed
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if(mouseEvent->button() == Qt::LeftButton)
                {
                    this->reject();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            // pass the event on to the parent class
            return QDialog::eventFilter(obj, event);
        }
}

void CMessageBox::on_btnOk_clicked()
{
    this->accept();
}

void CMessageBox::on_btnCancel_clicked()
{
    this->reject();
}
