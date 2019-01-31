#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_backButton_clicked()
{
    emit(backButtonClicked());
}

void Form::on_submitButton_clicked()
{
    QString name = ui->nameLineEdit->text(),
            surname = ui->surnameLineEdit->text();
    if (name == "" || surname == "")
        return;
    emit(submitButtonClicked(name, surname));
}
