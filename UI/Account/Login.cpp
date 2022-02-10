#include "Login.h"
#include "ui_Login.h"
#include <QScreen>
#include <QDebug>
bool Login::MainTainUser=false;

bool Login::isMainTain()
{
    return m_isMainTain;
}

void Login::setIsMainTain(bool value)
{
    m_isMainTain=value;
    emit isMainTainChanged();
}

Login::Login(QWidget *parent) :
    QDialog(parent),m_setting(new QSettings(QApplication::applicationDirPath()+"/config.ini",QSettings::IniFormat)),m_account(new Account(this)),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //setFixedSize(1920,1080);
    QRect deskRect = QGuiApplication::screens().at(0)->availableGeometry();
    setFixedSize(deskRect.width(),deskRect.height());
    ui->label_14->installEventFilter(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_3->setContextMenuPolicy(Qt::NoContextMenu);
    ui->stackedWidget->setCurrentIndex(1);
    m_keyBoard=new GKeyBoard;
    connect(m_keyBoard,&GKeyBoard::sigKeyboard,[this](QString value){
        if(ui->stackedWidget->currentIndex()==1) ui->lineEdit_2->insert(value);
        else if(ui->stackedWidget->currentIndex()==0){
            m_currentLine->insert(value);
        }

    });
    connect(m_keyBoard,&GKeyBoard::sigKeyBoardback,[this]{
        if(ui->stackedWidget->currentIndex()==1){
            ui->lineEdit_2->setSelection(ui->lineEdit_2->text().length()-1,ui->lineEdit_2->text().length());
            ui->lineEdit_2->del();
        }
        else if(ui->stackedWidget->currentIndex()==0){
            m_currentLine->setSelection(m_currentLine->text().length()-1,m_currentLine->text().length());
            m_currentLine->del();
        }
    });
//    connect(ui->pushButton_9,&QPushButton::clicked,this,&Login::on_pushButton_8_clicked);
//    connect(ui->pushButton_10,&QPushButton::clicked,this,&Login::on_pushButton_8_clicked);
    init();
}

Login::~Login()
{
    delete ui;
}

void Login::init()
{
    bool flag = m_setting->value("password/rememberPswd",true).toBool();
    if(flag){
        m_isLoadPassword=flag;
        if(m_isLoadPassword){
            ui->pushButton_7->setStyleSheet("border-image: url(:/Image/image/user/selected.png)");
        }else{
            ui->pushButton_7->setStyleSheet("border-image: url(:/Image/image/user/unselected.png);");
        }
        ui->lineEdit_2->setText(m_setting->value("password/password","").toString());
    }
    if(m_setting->value("password/username","").toString()=="normalone"){
        ui->pushButton_6->setStyleSheet("font-size: 34px;color: #000000;"
                                        "border-radius: 7px;border: 4px solid #967A50;");
        ui->pushButton_5->setStyleSheet("font-size: 34px;color: #666666;");
    }else if(m_setting->value("password/username","").toString()=="admin"){
        ui->pushButton_5->setStyleSheet("font-size: 34px;color: #000000;"
                                        "border-radius: 7px;border: 4px solid #967A50;");
        ui->pushButton_6->setStyleSheet("font-size: 34px;color: #666666;");
    }
    m_userName=m_setting->value("password/username","normalone").toString();
}

bool Login::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->label_14){
        if(event->type()==QEvent::MouseButtonPress){
            QMouseEvent* e=static_cast<QMouseEvent*>(event);
            if(e->button()==Qt::LeftButton){
                on_pushButton_7_clicked();
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return Login::eventFilter(watched, event);
    }
}

void Login::on_pushButton_2_clicked()
{
    //if(m_account->queryPassword(m_userName)==ui->lineEdit_2->text()){
        MainTainUser=true;
        setIsMainTain(true);
        QDialog::accept();
    //}else{
    //    CMessageBox::ShowInfo("密码错误",this,CMessageBox::StandardButton::OK);
    //}
}


void Login::on_pushButton_6_clicked()
{
    m_userName="normalone";
    ui->pushButton_6->setStyleSheet("font-size: 34px;color: #000000;"
                                    "border-radius: 7px;border: 4px solid #967A50;");
    ui->pushButton_5->setStyleSheet("font-size: 34px;color: #666666;");
}


void Login::on_pushButton_5_clicked()
{
    m_userName="admin";
    ui->pushButton_5->setStyleSheet("font-size: 34px;color: #000000;"
                                    "border-radius: 7px;border: 4px solid #967A50;");
    ui->pushButton_6->setStyleSheet("font-size: 34px;color: #666666;");
}


void Login::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Login::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Login::on_pushButton_3_clicked()
{
    if(m_account->queryPassword(m_userName)==ui->lineEdit_2->text()){
        MainTainUser=false;
        setIsMainTain(false);
        QDialog::accept();
        m_setting->setValue("password/password",ui->lineEdit_2->text());
        m_setting->setValue("password/username",m_userName);
    }else{
        CMessageBox::ShowInfo("密码错误",this,CMessageBox::StandardButton::OK);
    }
}


void Login::on_pushButton_7_clicked()
{
    m_isLoadPassword=!m_isLoadPassword;
    if(m_isLoadPassword){
        ui->pushButton_7->setStyleSheet("border-image: url(:/Image/image/user/selected.png)");
    }else{
        ui->pushButton_7->setStyleSheet("border-image: url(:/Image/image/user/unselected.png);");
    }
    m_setting->setValue("password/rememberPswd",m_isLoadPassword);
    //ui->label_14->setText("");
}


void Login::on_pushButton_8_clicked()
{
    if(m_keyBoard){
        m_keyBoard->move(ui->lineEdit_2->mapToGlobal(QPoint(0,0)).x()-m_keyBoard->width()-100,ui->lineEdit_2->mapToGlobal(QPoint(0,0)).y()-150);
        //m_keyBoard->move(ui->lineEdit_2->x()-(m_keyBoard->width()+100),ui->lineEdit_2->y()-100);
        m_keyBoard->showKeyboard();
        m_keyBoard->exec();
    }
}




void Login::on_pushButton_9_clicked()
{
    m_currentLine=ui->lineEdit_3;
    if(m_keyBoard){
        m_keyBoard->move(ui->lineEdit_2->mapToGlobal(QPoint(0,0)).x()-m_keyBoard->width()-100,ui->lineEdit_2->mapToGlobal(QPoint(0,0)).y()-150);
        //m_keyBoard->move(ui->lineEdit_2->x()-(m_keyBoard->width()+100),ui->lineEdit_2->y()-100);
        m_keyBoard->showKeyboard();
        m_keyBoard->exec();
    }
}


void Login::on_pushButton_10_clicked()
{
    m_currentLine=ui->lineEdit;
    if(m_keyBoard){
        m_keyBoard->move(ui->lineEdit_2->mapToGlobal(QPoint(0,0)).x()-m_keyBoard->width()-100,ui->lineEdit_2->mapToGlobal(QPoint(0,0)).y()-150);
        //m_keyBoard->move(ui->lineEdit_2->x()-(m_keyBoard->width()+100),ui->lineEdit_2->y()-100);
        m_keyBoard->showKeyboard();
        m_keyBoard->exec();
    }
}

