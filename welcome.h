#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>

namespace Ui {
class Welcome;
}

class Welcome : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();
signals:
    void startButtonClicked();

private slots:
    void on_startButton_clicked();

private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
