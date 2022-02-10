#ifndef GKEYBOARD_H
#define GKEYBOARD_H

#include <QDialog>
#include <QHBoxLayout>
#include <QQuickWidget>
#include <QQuickItem>
#include <QVariant>
class GKeyBoard:public QDialog
{
    Q_OBJECT
public:
    explicit GKeyBoard(QDialog* parent=nullptr);
    void showKeyboard();
signals:
    void sigKeyboard(QString);
    void sigKeyBoardback();
private slots:
    void slotGetKeyboard(QVariant);
    void slotKeyBoardback();
    void slotKeyBoardclose();
private:
    QQuickWidget* m_quickWidget {nullptr};
};

#endif // GKEYBOARD_H
