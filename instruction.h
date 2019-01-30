#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>

namespace Ui {
class Instruction;
}

class Instruction : public QWidget
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = nullptr);
    ~Instruction();

signals:
    void backButtonClicked();

    void continueButtonClicked();

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::Instruction *ui;
};

#endif // INSTRUCTION_H
