#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QString>
#include <QDebug>
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
    void keyPressed(int);

private slots:
    void goToFormWidget();

    void goToWelcomeWidget();

    void goToInstructionWidget(QString, QString);

    void startTest();

private:
    Ui::MainWindow *ui;
    Welcome *welcomeWidget;
    Form *formWidget;
    Instruction *instructionWidget;
    Quiz *quizWidget;
    QString name_, surname_;
};

#endif // MAINWINDOW_H
