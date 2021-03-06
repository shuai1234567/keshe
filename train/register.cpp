#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->activateWindow();
    ui->lineEdit_7->setPlaceholderText("11位数字");
    QRegExp regExp2("[0-9]*");
    ui->lineEdit_7->setValidator(new QRegExpValidator(regExp2,this));
    ui->lineEdit_7->setMaxLength(11);

    ui->lineEdit->setPlaceholderText("10位以内小写字母或大写字母开头");
    QRegExp regExp("[A-Za-z][A-Za-z0-9]*");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->lineEdit->setMaxLength(10);

    QRegExp regExp1("[A-Za-z0-9]*[@][A-Za-z0-9.]*");
    ui->lineEdit_8->setValidator(new QRegExpValidator(regExp1,this));

    ui->lineEdit_6->setValidator(new QRegExpValidator(regExp2,this));
    ui->lineEdit_6->setMaxLength(18);

    ui->lineEdit->setEchoMode(QLineEdit::Normal);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Normal);
    ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
    ui->lineEdit_7->setEchoMode(QLineEdit::Normal);
    ui->lineEdit_8->setEchoMode(QLineEdit::Normal);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    QString result;
    QString Accountname;
    int account;
    QString account1;
    QSqlQuery query;
    if(ui->lineEdit_2->text() != ui->lineEdit_3->text())
    {
        QMessageBox::critical(this,"错误",tr("两次输入密码不相同"));
        return;
    }

    if(ui->lineEdit->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写用户名！"));
        return;
    }
    if(ui->lineEdit_2->text() == "" or ui->lineEdit_3->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写密码！"));
        return;
    }
    if(ui->lineEdit_4->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写姓名！"));
        return;
    }
    if(ui->lineEdit_6->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写证件号码！"));
        return;
    }
    if(ui->lineEdit_7->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写手机号！"));
        return;
    }
    if(ui->lineEdit_8->text() == "")
    {
        QMessageBox::critical(this,"错误",tr("未填写电子邮箱！"));
        return;
    }
    if(!ui->radioButton->isChecked())
    {
        QMessageBox::critical(this,"错误",tr("未同意注册协议！"));
        return;
    }

    result = "select Accountname from Account" ;
    query.exec(result);
    while(query.next())
    {
        Accountname = query.value(0).toString();
        if(ui->lineEdit->text() == Accountname){
            QMessageBox::critical(this,"错误",tr("用户名已存在"));
            return;
        }
    }
    result = "select PhoneNumber from Account" ;
    query.exec(result);
    while(query.next())
    {
        Accountname = query.value(0).toString();
        if(ui->lineEdit_7->text() == Accountname){
            QMessageBox::critical(this,"错误",tr("手机号已存在"));
            return;
        }
    }
    result = "select Email from Account" ;
    query.exec(result);
    while(query.next())
    {
        Accountname = query.value(0).toString();
        if(ui->lineEdit_8->text() == Accountname){
            QMessageBox::critical(this,"错误",tr("邮箱已存在"));
            return;
        }
    }
    result = "select IDNumber from Account" ;
    query.exec(result);
    while(query.next())
    {
        Accountname = query.value(0).toString();
        if(ui->lineEdit_6->text() == Accountname){
            QMessageBox::critical(this,"错误",tr("身份证号已存在"));
            return;
        }
    }

    result="select max(AccountNumber) as a from Account";
    query.exec(result);
    while(query.next())
    {
        account = query.value(0).toInt() + 1;
    }
    account1 = QString::number(account, 10);
    QString U;
    U = "U";
    result = "insert into Account(IDNumber,Password,AccountNumber,Name,AccountName,IDType,Type,PhoneNumber,Email) values('"+ui->lineEdit_6->text()+"','"+ui->lineEdit_2->text()+"','"+account1+"','"+ui->lineEdit_4->text()+"','"+ui->lineEdit->text()+"','"+ui->comboBox->currentText()+"','"+U+"','"+ui->lineEdit_7->text()+"','"+ui->lineEdit_8->text()+"');";
    qDebug("readString = %s",qPrintable(result));
    query.exec(result);
    QMessageBox::information(this,"成功",tr("注册成功！"));
    emit display(0);//跳转到登录界面
}
//,IDNumber,PhoneNumber,Email,Type,AcccountNumber
//"','"+ui->lineEdit_6->text()+"','"+ui->lineEdit_7->text()+"','"+ui->lineEdit_8->text()+"','U','"+account1+

void Register::on_pushButton_2_clicked()
{
    emit display(0);
}
