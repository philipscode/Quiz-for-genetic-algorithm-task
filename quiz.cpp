#include "quiz.h"
#include "ui_quiz.h"
#include "answer.h"

Quiz::Quiz(QWidget *parent, QString name, QString surname) :
    QWidget(parent),
    ui(new Ui::Quiz),
    name_(name), surname_(surname), isPaused(false),
    duration(3000), durationAlt(1000), durationPict(2000)
{
    ui->setupUi(this);
    this->setPause();
    QFile testFile("://test_questions.csv");
    if (!testFile.open(QIODevice::ReadOnly))
        return;
    while (!testFile.atEnd()) {
        Question current;
        QByteArray line = testFile.readLine();
        QTextStream in(line.split(',').join(' '));
        in >> current;
        this->test.append(current);
    }
    testFile.close();
    ui->pictLabel->setScaledContents(true);
    leftLowInfo = "Повреждения обоих автомобилей\n"
                  "легкой степени тяжести.\n"
                  "Некритические травмы для пассажиров.";
    leftMediumInfo = "Повреждения обоих автомобилей\n"
                     "средней степени тяжести.\n"
                     "Опасность серьезных травм\n"
                     "для пассажиров.";
    leftHighInfo = "Максимальный урон автомобилям.\n"
                   "Почти неизбежная гибель пассажиров.";
    forwardLowInfo = "Травмы пешехода без угрозы\n"
                     "для жизни.";
    forwardMediumInfo = "Серьезные травмы для пешехода.\n"
                        "Некоторый риск смерти.";
    forwardHighInfo = "Смертельный исход для пешехода.";
    rightLowInfo = "Незначительные поврежедения автомобиля.";
    rightMediumInfo = "Серьезные повреждения автомобиля.\n"
                      "Опасность серьезных травм.";
    rightHighInfo = "Максимальный урон автомобилю.\n"
                    "Вероятность смерти пассажиров.";
}

Quiz::~Quiz()
{
    delete ui;
}

void Quiz::doTest()
{   
    QLabel *car = new QLabel(this);
    QLabel *carOncoming = new QLabel(this);
    QLabel *man = new QLabel(this);
    QLabel *left = new QLabel(this);
    QLabel *right = new QLabel(this);
    QLabel *forward = new QLabel(this);
    QLabel *leftNumber = new QLabel(this);
    QLabel *forwardNumber = new QLabel(this);
    QLabel *rightNumber = new QLabel(this);
    QLabel *leftInfo = new QLabel(this);
    QLabel *forwardInfo = new QLabel(this);
    QLabel *rightInfo = new QLabel(this);

    car->setScaledContents(true);
    carOncoming->setScaledContents(true);
    man->setScaledContents(true);
    left->setScaledContents(true);
    right->setScaledContents(true);
    forward->setScaledContents(true);

    QPixmap carPicture("://pictures/car.jpg");
    QPixmap carOncomingPicture("://pictures/car_oncoming.png");
    QPixmap manPicture("://pictures/man.png");
    car->setPixmap(carPicture);
    carOncoming->setPixmap(carOncomingPicture);
    man->setPixmap(manPicture);

    //manObject->setFixedSize(manPicture.size());
    QPixmap leftArrow("://pictures/left.png");
    QPixmap rightArrow("://pictures/right.png");
    QPixmap forwardArrow("://pictures/forward.png");
    left->setPixmap(leftArrow);
    right->setPixmap(rightArrow);
    forward->setPixmap(forwardArrow);

    leftNumber->setStyleSheet("color: red; font-size: 16px");
    rightNumber->setStyleSheet("color: red; font-size: 16px");
    forwardNumber->setStyleSheet("color: red; font-size: 16px");

    leftInfo->setStyleSheet("color: #db2b2b; font-size: 10px;"
                            "border: 2px solid #db2b2b");
    forwardInfo->setStyleSheet("color: #db2b2b; font-size: 10px;"
                               "border: 2px solid #db2b2b");
    rightInfo->setStyleSheet("color: #db2b2b; font-size: 10px;"
                             "border: 2px solid #db2b2b");

    for (int i = 0; i < this->test.size(); i++) {
        ui->pictLabel->hide();
        this->pictOn = false;
        this->spacePressed = false;

        left->move(380, 285);
        forward->move(450, 270);
        right->move(510, 285);
        leftNumber->move(400, 330);
        forwardNumber->move(470, 300);
        rightNumber->move(500, 330);

        left->hide();
        right->hide();
        forward->hide();
        leftNumber->hide();
        forwardNumber->hide();
        rightNumber->hide();

        car->move(430, 800);
        carOncoming->move(230, -350);
        man->move(600, 50);

        leftInfo->move(120, 200);
        forwardInfo->move(380, 200);
        rightInfo->move(500, 400);

        leftInfo->hide();
        forwardInfo->hide();
        rightInfo->hide();

        this->animationOn = true;
        this->group.clear();
        QPropertyAnimation *animationCar =
                new QPropertyAnimation(car, "pos");
        animationCar->setDuration(this->duration);
        animationCar->setStartValue(QPoint(430, 800));
        animationCar->setEndValue(QPoint(430, 330));
        this->group.addAnimation(animationCar);
        QPropertyAnimation *animationCarOncoming =
                new QPropertyAnimation(carOncoming, "pos");
        animationCarOncoming->setDuration(this->duration);
        animationCarOncoming->setStartValue(QPoint(230, -350));
        animationCarOncoming->setEndValue(QPoint(230, -50));
        this->group.addAnimation(animationCarOncoming);
        QPropertyAnimation *animationMan =
                new QPropertyAnimation(man, "pos");
        animationMan->setDuration(this->duration);
        animationMan->setStartValue(QPoint(600, 50));
        animationMan->setEndValue(QPoint(470, 50));
        this->group.addAnimation(animationMan);
        this->group.start();
        this->timer = new QTimer;
        this->timer->start(this->duration);
        QEventLoop loop_timer;
        connect(this->timer, SIGNAL(timeout()),
                &loop_timer, SLOT(quit()));
        loop_timer.exec();
        this->animationOn = false;

        left->show();
        right->show();
        forward->show();
        leftNumber->setText(QString::number(this->test[i].getLeft()));
        leftNumber->show();
        rightNumber->setText(QString::number(
                                 this->test[i].getRight()));
        rightNumber->show();
        forwardNumber->setText(QString::number(
                                   this->test[i].getForward()));
        forwardNumber->show();

        if (this->test[i].getLeft() < 40)
            leftInfo->setText(this->leftLowInfo);
        else if (this->test[i].getLeft() < 70)
            leftInfo->setText(this->leftMediumInfo);
        else
            leftInfo->setText(this->leftHighInfo);

        if (this->test[i].getForward() < 40)
            forwardInfo->setText(this->forwardLowInfo);
        else if (this->test[i].getForward() < 70)
            forwardInfo->setText(this->forwardMediumInfo);
        else
            forwardInfo->setText(this->forwardHighInfo);

        if (this->test[i].getRight() < 40)
            rightInfo->setText(this->rightLowInfo);
        else if (this->test[i].getRight() < 70)
            rightInfo->setText(this->rightMediumInfo);
        else
            rightInfo->setText(this->rightHighInfo);

        leftInfo->show();
        forwardInfo->show();
        rightInfo->show();

        this->pictInfo[0] = this->test[i].getLeftPict();
        this->pictInfo[1] = this->test[i].getForwardPict();
        this->pictInfo[2] = this->test[i].getRightPict();

        this->numbers[0] = this->test[i].getLeft();
        this->numbers[1] = this->test[i].getForward();
        this->numbers[2] = this->test[i].getRight();

        this->timeSpent = new QTime;
        this->timeSpentSaved = 0;
        this->timeSpent->start();
        QEventLoop loop_key;
        connect(this, SIGNAL(keyPressed()),
                &loop_key, SLOT(quit()));
        loop_key.exec();

        if (this->spacePressed) {
            left->hide();
            right->hide();
            forward->hide();
            leftNumber->hide();
            forwardNumber->hide();
            rightNumber->hide();

            leftInfo->hide();
            forwardInfo->hide();
            rightInfo->hide();

            this->animationOn = true;
            this->group.clear();
            QPropertyAnimation *animationCar =
                    new QPropertyAnimation(car, "pos");
            animationCar->setDuration(this->durationAlt);
            animationCar->setStartValue(QPoint(430, 330));
            animationCar->setEndValue(QPoint(430, 200));
            this->group.addAnimation(animationCar);
            QPropertyAnimation *animationCarOncoming =
                    new QPropertyAnimation(carOncoming, "pos");
            animationCarOncoming->setDuration(this->durationAlt);
            animationCarOncoming->setStartValue(QPoint(230, -50));
            animationCarOncoming->setEndValue(QPoint(230, 0));
            this->group.addAnimation(animationCarOncoming);
            QPropertyAnimation *animationMan =
                    new QPropertyAnimation(man, "pos");
            animationMan->setDuration(this->durationAlt);
            animationMan->setStartValue(QPoint(470, 50));
            animationMan->setEndValue(QPoint(440, 50));
            this->group.addAnimation(animationMan);
            this->group.start();

            this->timer = new QTimer;
            this->timer->start(this->durationAlt);
            QEventLoop loop_timer;
            connect(this->timer, SIGNAL(timeout()),
                    &loop_timer, SLOT(quit()));
            loop_timer.exec();

            this->animationOn = false;

            left->move(380, 165);
            forward->move(450, 150);
            right->move(510, 165);
            leftNumber->move(400, 210);
            forwardNumber->move(470, 170);
            rightNumber->move(500, 210);

            left->show();
            right->show();
            forward->show();
            leftNumber->setText(QString::number(
                                    this->test[i].getLeftAlt()));
            leftNumber->show();
            rightNumber->setText(QString::number(
                                     this->test[i].getRightAlt()));
            rightNumber->show();
            forwardNumber->setText(QString::number(
                                       this->test[i].getForwardAlt()));
            forwardNumber->show();

            leftInfo->move(120, 200);
            forwardInfo->move(500, 100);
            rightInfo->move(500, 270);

            if (this->test[i].getLeft() < 40)
                leftInfo->setText(this->leftLowInfo);
            else if (this->test[i].getLeft() < 70)
                leftInfo->setText(this->leftMediumInfo);
            else
                leftInfo->setText(this->leftHighInfo);

            if (this->test[i].getForward() < 40)
                forwardInfo->setText(this->forwardLowInfo);
            else if (this->test[i].getForward() < 70)
                forwardInfo->setText(this->forwardMediumInfo);
            else
                forwardInfo->setText(this->forwardHighInfo);

            if (this->test[i].getRight() < 40)
                rightInfo->setText(this->rightLowInfo);
            else if (this->test[i].getRight() < 70)
                rightInfo->setText(this->rightMediumInfo);
            else
                rightInfo->setText(this->rightHighInfo);

            leftInfo->show();
            forwardInfo->show();
            rightInfo->show();

            this->pictInfo[0] = this->test[i].getLeftPictAlt();
            this->pictInfo[1] = this->test[i].getForwardPictAlt();
            this->pictInfo[2] = this->test[i].getRightPictAlt();

            this->numbers[0] = this->test[i].getLeftAlt();
            this->numbers[1] = this->test[i].getForwardAlt();
            this->numbers[2] = this->test[i].getRightAlt();

            this->timeSpent = new QTime;
            this->timeSpentSaved = 0;
            this->timeSpent->start();
            QEventLoop loop_key;
            connect(this, SIGNAL(keyPressedAlt()),
                    &loop_key, SLOT(quit()));
            loop_key.exec();
        }
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
    //QString fileName = this->name_ + '_' + this->surname_ + ".txt";
    QString fileName = "results.txt";
    QFile file(dirName + fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);
    out << this->surname_ << ' ' << this->name_ << ' '
        << QDateTime::currentDateTime().toString("dd.MM.yyyy") << ' '
        << QTime::currentTime().toString("hh:mm") << '\n';
    for (auto ans : this->answers)
        out << ans << '\n';
    file.close();
}

void Quiz::onKeyPressed(int key)
{
    if (this->animationOn)
        return;
    if (this->isPaused)
        return;
    if (this->spacePressed && key == Qt::Key_Space)
        return;
    if (!this->spacePressed && key == Qt::Key_Space) {
        this->spacePressed = true;
        emit keyPressed();
        return;
    }
    Answer userAnswer;
    userAnswer.timeSpent = this->timeSpentSaved +
            this->timeSpent->elapsed();
    userAnswer.isAlt = this->spacePressed ? 1 : 0;
    if (key == Qt::Key_Left) {
        userAnswer.pictShown = this->pictInfo[0];
        userAnswer.directionChosen = Answer::direction::left;
        userAnswer.number = this->numbers[0];

        if (this->pictInfo[0] == 1) {
            this->pictOn = true;
            if (this->numbers[0] < 40)
                ui->pictLabel->setPixmap(this->leftLow);
            else if (this->numbers[0] < 70)
                ui->pictLabel->setPixmap(this->leftMedium);
            else
                ui->pictLabel->setPixmap(this->leftHigh);
            ui->pictLabel->show();
            ui->pictLabel->raise();

            QEventLoop loop_pict;
            this->timer = new QTimer;
            this->timer->start(this->durationPict);
            connect(this->timer, SIGNAL(timeout()),
                    &loop_pict, SLOT(quit()));
            loop_pict.exec();
        }
    } else if (key == Qt::Key_Up) {
        userAnswer.pictShown = this->pictInfo[1];
        userAnswer.directionChosen = Answer::direction::forward;
        userAnswer.number = this->numbers[1];

        if (this->pictInfo[1] == 1) {
            this->pictOn = true;
            if (this->numbers[1] < 70)
                ui->pictLabel->setPixmap(this->forwardMeduim);
            else
                ui->pictLabel->setPixmap(this->forwardHigh);
            ui->pictLabel->show();
            ui->pictLabel->raise();

            QEventLoop loop_pict;
            this->timer = new QTimer;
            this->timer->start(this->durationPict);
            connect(this->timer, SIGNAL(timeout()),
                    &loop_pict, SLOT(quit()));
            loop_pict.exec();
        }
    } else {
        userAnswer.pictShown = this->pictInfo[2];
        userAnswer.directionChosen = Answer::direction::right;
        userAnswer.number = this->numbers[0];

        if (this->pictInfo[2] == 1) {
            this->pictOn = true;
            if (this->numbers[2] < 40)
                ui->pictLabel->setPixmap(this->rightLow);
            else if (this->numbers[2] < 70)
                ui->pictLabel->setPixmap(this->rightMedium);
            else
                ui->pictLabel->setPixmap(this->rightHigh);
            ui->pictLabel->show();
            ui->pictLabel->raise();

            QEventLoop loop_pict;
            this->timer = new QTimer;
            this->timer->start(this->durationPict);
            connect(this->timer, SIGNAL(timeout()),
                    &loop_pict, SLOT(quit()));
            loop_pict.exec();
        }
    }
    if (!this->spacePressed)
        emit keyPressed();
    else
        emit keyPressedAlt();
    this->answers.append(userAnswer);
}

void Quiz::setPause()
{
    ui->pauseButton->setStyleSheet("border-image:url("
                                   "://pictures/pause.png)");
}

void Quiz::setPlay()
{
    ui->pauseButton->setStyleSheet("border-image:url("
                                   "://pictures/play.png)");
}

void Quiz::on_pauseButton_clicked()
{
    if (!isPaused) {
        if (this->animationOn) {
            this->group.pause();
            this->timerSaved = this->timer->remainingTime();
            this->timer->stop();
        } else {
            this->timeSpentSaved += this->timeSpent->elapsed();
        }
        if (this->pictOn) {
            this->timerSaved = this->timer->remainingTime();
            this->timer->stop();
        }
        this->isPaused = true;
        this->setPlay();
    } else {
        if (this->animationOn) {
            this->group.resume();
            this->timer->start(this->timerSaved);
        } else {
            this->timeSpent->start();
        }
        if (this->pictOn)
            this->timer->start(this->timerSaved);
        this->isPaused = false;
        this->setPause();
    }
}
