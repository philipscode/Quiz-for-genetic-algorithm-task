#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "welcome.h"
#include "instruction.h"

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
    void goToInstructionWidget();

private:
    Ui::MainWindow *ui;
    Welcome *startWidget;
    Instruction *instructionWidget;
};

#endif // MAINWINDOW_H
