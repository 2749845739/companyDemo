#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QStyle>
#include <QMouseEvent>
#include <QSettings>
#include "CMessageBox.h"
#include "Account.h"
#include "GKeyBoard.h"
#include "QLineEdit"
namespace Ui {
class Login;
}
class Login : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool isMainTain READ isMainTain WRITE setIsMainTain NOTIFY isMainTainChanged)
public:
    bool isMainTain();
    void setIsMainTain(bool value);
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    static bool MainTainUser;
    void init();
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void isMainTainChanged();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Login *ui;
    bool m_isMainTain;
    bool m_isLoadPassword {false};
    QSettings* m_setting;
    Account* m_account {nullptr};
    QString m_userName;
    GKeyBoard* m_keyBoard {nullptr};
    QLineEdit* m_currentLine {nullptr};
};


#endif // LOGIN_H
