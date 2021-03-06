#ifndef ADMMENU_H
#define ADMMENU_H

#include <QWidget>
#include <addtrain.h>

namespace Ui {
class AdmMenu;
}

class AdmMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AdmMenu(QWidget *parent = 0);
    ~AdmMenu();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::AdmMenu *ui;
};

#endif // ADMMENU_H
