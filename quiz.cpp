#include "quiz.h"
#include "ui_quiz.h"
#include "answer.h"

Quiz::Quiz(QWidget *parent, QString name, QString surname) :
    QWidget(parent),
    ui(new Ui::Quiz),
    name_(name), surname_(surname)
{
    ui->setupUi(this);
    this->setPause();
    QString fileName = "://test_questions.txt";
    QFile testFile(fileName);
    if (!testFile.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&testFile);
    while (!in.atEnd()) {
        Question current;
        in >> current;
        test.append(current);
    }
    test.pop_back();
}

Quiz::~Quiz()
{
    delete ui;
}

void Quiz::doTest()
{
    QLabel *car = new QLabel(this);
    QLabel *object = new QLabel(this);
    QLabel *left = new QLabel(this);
    QLabel *right = new QLabel(this);
    QLabel *forward = new QLabel(this);
    QLabel *leftNumber = new QLabel(this);
    QLabel *forwardNumber = new QLabel(this);
    QLabel *rightNumber = new QLabel(this);
    car->setScaledContents(true);
    object->setScaledContents(true);
    left->setScaledContents(true);
    right->setScaledContents(true);
    forward->setScaledContents(true);
    QPixmap carPicture("://pictures/car.jpg");
    QPixmap manObject("://pictures/man.png");
    QPixmap dogObject("://pictures/dog.png");
    car->setPixmap(carPicture);
    QPixmap leftArrow("://pictures/left.png");
    QPixmap rightArrow("://pictures/right.png");
    QPixmap forwardArrow("://pictures/forward.png");
    left->setPixmap(leftArrow);
    right->setPixmap(rightArrow);
    forward->setPixmap(forwardArrow);
    left->move(350, 140);
    forward->move(450, 140);
    right->move(540, 140);
    leftNumber->setStyleSheet("color: red; font-size: 16px");
    rightNumber->setStyleSheet("color: red; font-size: 16px");
    forwardNumber->setStyleSheet("color: red; font-size: 16px");
    leftNumber->move(370, 190);
    forwardNumber->move(450, 190);
    rightNumber->move(540, 190);
    for (int i = 0; i < test.size(); i++) {
        left->hide();
        right->hide();
        forward->hide();
        leftNumber->hide();
        forwardNumber->hide();
        rightNumber->hide();
        car->move(420, 500);
        object->move(600, 50);
        this->animationOn = true;
        if (test[i].getObjectType() == "man") {
            object->setPixmap(manObject);
            object->setFixedSize(manObject.size());
        } else {
            object->setPixmap(dogObject);
            object->setFixedSize(dogObject.size());
        }
        QParallelAnimationGroup group;
        QPropertyAnimation *animationCar =
                new QPropertyAnimation(car, "pos");
        animationCar->setDuration(3000);
        animationCar->setStartValue(QPoint(420, 500));
        animationCar->setEndValue(QPoint(420, 220));
        group.addAnimation(animationCar);
        QPropertyAnimation *animationObject =
                new QPropertyAnimation(object, "pos");
        animationObject->setDuration(3000);
        animationObject->setStartValue(QPoint(600, 50));
        animationObject->setEndValue(QPoint(430, 50));
        group.addAnimation(animationObject);
        group.start();
        QTimer *timer = new QTimer;
        timer->start(3000);
        QEventLoop loop_1;
        connect(timer, SIGNAL(timeout()),
                &loop_1, SLOT(quit()));
        loop_1.exec();
        animationOn = false;
        left->show();
        right->show();
        forward->show();
        leftNumber->setText(QString::number(test[i].getLeft()));
        leftNumber->show();
        rightNumber->setText(QString::number(test[i].getRight()));
        rightNumber->show();
        forwardNumber->setText(QString::number(test[i].getForward()));
        forwardNumber->show();
        this->timeSpent = new QTime;
        timeSpent->start();
        QEventLoop loop_2;
        connect(this, SIGNAL(keyPressed()),
                &loop_2, SLOT(quit()));
        loop_2.exec();
    }
    this->saveAnswers();
}

void Quiz::saveAnswers() const
{
    QString dirName = QStandardPaths::writableLocation(
                QStandardPaths::DocumentsLocation) +
            QDir::separator() + "QUIZ_RESULTS" + QDir::separator();
    if (!QDir(dirName).exists())
        QDir().mkdir(dirName);
    QString fileName = name_ + '_' + surname_ + ".txt";
    QFile file(dirName + fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for (auto ans : answers)
        out << ans << '\n';
    file.close();
}

void Quiz::onKeyPressed(int key)
{
    if (animationOn)
        return;
    Answer userAnswer;
    userAnswer.timeSpent = this->timeSpent->elapsed();
    if (key == Qt::Key_Left)
        userAnswer.directionChosen = Answer::direction::left;
    else if (key == Qt::Key_Up)
        userAnswer.directionChosen = Answer::direction::forward;
    else
        userAnswer.directionChosen = Answer::direction::right;
    answers.append(userAnswer);
    emit keyPressed();
}

void Quiz::setPause()
{
    ui->pauseButton->setStyleSheet("border-image:url("
                                   "://pictures/pause.png)");
}

void Quiz::setPlay()
{
    QPixmap pixmap("://pictures/play.png");
    QIcon ButtonIcon(pixmap);
    ui->pauseButton->setIcon(ButtonIcon);
    ui->pauseButton->setIconSize(pixmap.rect().size());
}
