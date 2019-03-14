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

/*void MainWindow::goToFormWidget() //test
{
    this->startTest();
}*/

void MainWindow::goToFormWidget() {
    formWidget = new Form;
    connect(formWidget, SIGNAL(backButtonClicked()),
            this, SLOT(goToWelcomeWidget()));
    connect(formWidget, SIGNAL(submitButtonClicked(QString, QString)),
            this, SLOT(goToInstructionWidget(QString, QString)));
    this->setCentralWidget(formWidget);
}

void MainWindow::goToInstructionWidget(QString name, QString surname)
{
    name_ = name;
    surname_ = surname;
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
    //quizWidget = new Quiz(); //test
    quizWidget = new Quiz(nullptr, name_, surname_);
    connect(this, SIGNAL(keyPressed(int)),
            quizWidget, SLOT(onKeyPressed(int)));
    this->setCentralWidget(quizWidget);
    this->setStyleSheet("");
    QPixmap bkgnd("://pictures/road.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    quizWidget->doTest();
    finalWidget = new Final();
    this->setCentralWidget(finalWidget);
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    if (ke->key() == Qt::Key_Left ||
        ke->key() == Qt::Key_Up ||
        ke->key() == Qt::Key_Right ||
        ke->key() == Qt::Key_Space)
        emit keyPressed(ke->key());
}
