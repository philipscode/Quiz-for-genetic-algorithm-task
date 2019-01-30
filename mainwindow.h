#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "welcome.h"
#include "form.h"
#include "instruction.h"
#include "quiz.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent*);

signals:
    void keyPressed();

private slots:
    void goToFormWidget();

    void goToWelcomeWidget();

    void goToInstructionWidget();

    void startTest();

private:
    Ui::MainWindow *ui;
    Welcome *welcomeWidget;
    Form *formWidget;
    Instruction *instructionWidget;
    Quiz *quizWidget;
};

#endif // MAINWINDOW_H
