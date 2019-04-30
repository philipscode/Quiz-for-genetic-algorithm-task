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
    this->setWindowTitle("Программа-опрос для составления генетического"
                         " алгоритма");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToFormWidget() {
    //this->startTest();
    formWidget = new Form;
    connect(formWidget, SIGNAL(submitButtonClicked(QString)),
            this, SLOT(goToInstructionWidget(QString)));
    this->setCentralWidget(formWidget);
}

void MainWindow::goToInstructionWidget(QString userName)
{
    this->userName_ = userName;
    instructionWidget = new Instruction;
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
    //quizWidget = new Quiz(); //test
    quizWidget = new Quiz(nullptr, this->userName_);
    this->setCentralWidget(quizWidget);
    this->setStyleSheet("");
    QPixmap bkgnd("://pictures/road-light.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    quizWidget->doTest();
    finalWidget = new Final();
    this->setCentralWidget(finalWidget);
}
