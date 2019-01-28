#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    startWidget(new Welcome),
    instructionWidget(new Instruction)
{
    ui->setupUi(this);
    this->setCentralWidget(startWidget);
    connect(startWidget, SIGNAL(startButtonClicked()),
            this, SLOT(goToInstructionWidget()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToInstructionWidget()
{
    this->setCentralWidget(instructionWidget);
}
