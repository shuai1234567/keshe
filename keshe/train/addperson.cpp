#include "addperson.h"
#include "ui_addperson.h"

extern QString AccountNumber1;
int k = 1;

AddPerson::AddPerson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPerson)
{
    ui->setupUi(this);
    QFile qssfile(":/style/base.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    this->setStyleSheet(qss);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("姓名"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("证件类型"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("证件号码"));
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    i = 0;
    QSqlQuery query;
    QString result;
    result = "select Name,IDType,IDNumber from Account where AccountNumber = '"+AccountNumber1+"';";
    query.exec(result);
    while(query.next())
    {
        i++;
        ui->tableWidget->setRowCount(i + 1);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
    }
}

AddPerson::~AddPerson()
{
    delete ui;
}

void AddPerson::on_pushButton_clicked()
{
    if(ui->tableWidget->rowCount() == 11){
        QMessageBox::critical(this,"错误",tr("每个账户最多可添加10位乘客！"));
        return;
    }
    int w = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(w);
}

void AddPerson::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "删除乘客", "是否要删除这名乘客?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        if(ui->tableWidget->currentRow() >= 2){
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
        else{
            QMessageBox::critical(this,"错误",tr("最少保留一名乘客"));
        }
    }
}

void AddPerson::on_pushButton_4_clicked()
{
    this->close();
}

void AddPerson::on_pushButton_3_clicked()
{
    QString AccountName;
    QString Password;
    QString PhoneNumber;
    QString Email;
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "保存乘客信息", "是否要保存乘客信息?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        for(int row = 1;row < ui->tableWidget->rowCount();row++){        
            if(ui->tableWidget->item(row, 0) == 0){
                QMessageBox::critical(this,"错误",tr("请填写姓名"));
                return;
            }
            if(ui->tableWidget->item(row, 1) == 0){
                QMessageBox::critical(this,"错误",tr("请填写证件类型"));
                return;
            }
            if(ui->tableWidget->item(row, 2) == 0){
                QMessageBox::critical(this,"错误",tr("请填写证件号码"));
                return;
            }
            if(ui->tableWidget->item(row, 1)->text() != "二代身份证" and ui->tableWidget->item(row, 1)->text() != "港澳台证" and ui->tableWidget->item(row, 1)->text() != "护照"){
                QMessageBox::critical(this,"错误",tr("证件类型请填写「二代身份证」或「港澳台证」或「护照」"));
                return;
            }
        }
        for(int roww = 0;roww < ui->tableWidget->rowCount();roww++)
        for(int rowq = roww+1;rowq < ui->tableWidget->rowCount();rowq++){
            if(ui->tableWidget->item(roww, 2)->text() == ui->tableWidget->item(rowq, 2)->text()){
                QMessageBox::critical(this,"错误",tr("有重复证件号"));
                return;
            }
        }
        for(int row = 1;row < ui->tableWidget->rowCount();row++){
            QString Number = ui->tableWidget->item(row, 2)->text();
            std::string str = Number.toStdString();
            const char* ch = str.c_str();
            for(i = 0 ;ch[i] != '\0';i++){
                if(ch[i] < '0' or ch[i] > '9'){
                    QMessageBox::critical(this,"错误",tr("证件号格式错误"));
                    return;
                }
                if(i > 17){
                    QMessageBox::critical(this,"错误",tr("证件号位数超过18位"));
                    return;
                }
            }
            qDebug() << i;
            if(i != 18){
                QMessageBox::critical(this,"错误",tr("证件号位数不足"));
                return;
            }

        }
        QSqlQuery query;
        QString result;
        result = "select AccountName,Password,PhoneNumber,Email from Account where AccountNumber = '"+AccountNumber1+"';";
        query.exec(result);
        while(query.next())
        {
            AccountName = query.value(0).toString();
            Password = query.value(1).toString();
            PhoneNumber = query.value(2).toString();
            Email = query.value(3).toString();
        }
        result = "delete from Account where AccountNumber = '"+AccountNumber1+"';";
        QString U = "U";
        query.exec(result);
        for(int row = 1;row < ui->tableWidget->rowCount();row++){
            result = "insert into Account(IDNumber,Password,AccountNumber,Name,AccountName,IDType,Type,PhoneNumber,Email) values('"+ui->tableWidget->item(row, 2)->text()+"','"+Password+"','"+AccountNumber1+"','"+ui->tableWidget->item(row, 0)->text()+"','"+AccountName+"','"+ui->tableWidget->item(row,1)->text()+"','"+U+"','"+PhoneNumber+"','"+Email+"');";
            query.exec(result);
        }
        QMessageBox::information(this,"成功",tr("乘客信息保存成功！"));
        k = 0;
    }
}
