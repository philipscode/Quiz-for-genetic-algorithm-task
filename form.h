#ifndef FORM_H
#define FORM_H

#include <QWidget>

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
    void backButtonClicked();

    void submitButtonClicked();

private slots:
    void on_backButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
