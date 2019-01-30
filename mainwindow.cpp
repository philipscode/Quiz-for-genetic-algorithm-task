#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    welcomeWidget(new Welcome)
{
    ui->setupUi(this);
    this->setCentralWidget(welcomeWidget);
    connect(welcomeWidget, SIGNAL(startButtonClicked()),
            this, SLOT(goToFormWidget()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToFormWidget() {
    formWidget = new Form;
    connect(formWidget, SIGNAL(backButtonClicked()),
            this, SLOT(goToWelcomeWidget()));
    connect(formWidget, SIGNAL(submitButtonClicked()),
            this, SLOT(goToInstructionWidget()));
    this->setCentralWidget(formWidget);
}

void MainWindow::goToInstructionWidget()
{
    instructionWidget = new Instruction;
    connect(instructionWidget, SIGNAL(backButtonClicked()),
            this, SLOT(goToFormWidget()));
    connect(instructionWidget, SIGNAL(continueButtonClicked()),
            this, SLOT(startTest()));
    this->setCentralWidget(instructionWidget);
}

void MainWindow::goToWelcomeWidget()
{
    welcomeWidget = new Welcome;
    connect(welcomeWidget, SIGNAL(startButtonClicked()),
            this, SLOT(goToFormWidget()));
    this->setCentralWidget(welcomeWidget);
}

void MainWindow::startTest()
{
    quizWidget = new Quiz;
    connect(this, SIGNAL(keyPressed()),
            quizWidget, SLOT(onKeyPressed()));
    this->setCentralWidget(quizWidget);
    quizWidget->doTest();
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    emit keyPressed();
}
