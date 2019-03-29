#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QString>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:

    void submitButtonClicked(QString);

private slots:

    void on_submitButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
