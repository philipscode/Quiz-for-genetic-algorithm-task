#ifndef FINAL_H
#define FINAL_H

#include <QWidget>

namespace Ui {
class Final;
}

class Final : public QWidget
{
    Q_OBJECT

public:
    explicit Final(QWidget *parent = nullptr);
    ~Final();

private:
    Ui::Final *ui;
};

#endif // FINAL_H
