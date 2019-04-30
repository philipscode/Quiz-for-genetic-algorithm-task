#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "welcome.h"
#include "form.h"
#include "instruction.h"
#include "quiz.h"
#include "final.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void goToFormWidget();

    void goToWelcomeWidget();

    void goToInstructionWidget(QString);

    void startTest();

private:
    Ui::MainWindow *ui;
    Welcome *welcomeWidget;
    Form *formWidget;
    Instruction *instructionWidget;
    Quiz *quizWidget;
    Final *finalWidget;
    QString userName_;
};

#endif // MAINWINDOW_H
