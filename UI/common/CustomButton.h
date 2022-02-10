#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QFile>
class CustomButton:public QPushButton
{
    //Q_PROPERTY(bool style READ style WRITE setStyle NOTIFY styleChanged)
    Q_OBJECT
public:
    //bool style();
    //void setStyle(bool value);
signals:
    //void styleChanged();
public:
    CustomButton(QWidget* parent=nullptr);
private:
    void readStylesheet();
private:
    bool m_style {false};
};

#endif // CUSTOMBUTTON_H
