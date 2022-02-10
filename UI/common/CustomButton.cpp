#include "CustomButton.h"

//bool CustomButton::style()
//{
//    return m_style;
//}

//void CustomButton::setStyle(bool value)
//{
//    m_style=value;
//    emit styleChanged();
//}

CustomButton::CustomButton(QWidget* parent):QPushButton(parent)
{
    setObjectName("BtnStyle");
    readStylesheet();
}

void CustomButton::readStylesheet()
{
    QFile file(":/Qss/customButton.qss");
     if(file.exists())
       {
         file.open(QFile::ReadOnly);
         QString styleSheet;
         styleSheet.append(file.readAll());
         setStyleSheet(styleSheet);
         file.close();
       }
}
