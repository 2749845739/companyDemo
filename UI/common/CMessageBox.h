#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class CMessageBox;
}

class CMessageBox : public QDialog
{
    Q_OBJECT

public:
    /********************************按钮类型********************************/
    enum class StandardButton :unsigned int
    {
        OK,
        YesNo
    };
    explicit CMessageBox(QWidget *parent = nullptr);
    ~CMessageBox();
    static int ShowInfo(const QString info,QWidget *parent,StandardButton standardButton=StandardButton::OK)
    {
        CMessageBox msg(parent);
        return msg.setInfo(info,standardButton);
    }
private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:

    int setInfo(const QString info,StandardButton standardButton);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    Ui::CMessageBox *ui;
    //鼠标是否按下属性
    bool m_bPressed=false;
    //按下后当前鼠标位置属性
    QPoint m_point;
};

#endif // CMESSAGEBOX_H
