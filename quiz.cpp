#include "quiz.h"
#include "ui_quiz.h"
#include "answer.h"

Quiz::Quiz(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::Quiz),
    userName_(userName), isPaused(false),
    duration(3000), durationAlt(1500), durationPict(2000)
{
    ui->setupUi(this);
    ui->pauseButton->setStyleSheet("border-image:url("
                                   "://pictures/pause.png)");
    QFile testFile("://test_questions.csv");
    if (!testFile.open(QIODevice::ReadOnly | QIODevice::Text))
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

    connect(this, SIGNAL(buttonClicked(int)),
            this, SLOT(onButtonClicked(int)));
    quizTimer = new QTimer(this);
    connect(quizTimer, SIGNAL(timeout()), this, SLOT(updateQuizTimer()));
    quizTimer->start(1000);
    quizTime.setHMS(0, 40, 0, 0);
    ui->countLabel->setText(quizTime.toString("m:ss"));
    finished = false;
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

    QPixmap carPicture("://pictures/car.png");
    QPixmap carOncomingPicture("://pictures/car_oncoming.png");
    QPixmap manPicture("://pictures/man.png");
    car->setPixmap(carPicture);
    carOncoming->setPixmap(carOncomingPicture);
    man->setPixmap(manPicture);

    QPixmap leftArrow("://pictures/left.png");
    QPixmap rightArrow("://pictures/right.png");
    QPixmap forwardArrow("://pictures/forward.png");
    left->setPixmap(leftArrow);
    right->setPixmap(rightArrow);
    forward->setPixmap(forwardArrow);

    QString numberStyle = "color: red; font-size: 16px";

    leftNumber->setStyleSheet(numberStyle);
    rightNumber->setStyleSheet(numberStyle);
    forwardNumber->setStyleSheet(numberStyle);

    QString infoStyle = "color: #db2b2b; font-size: 16px;"
                        "border: 2px solid #db2b2b; background-color: #e8b620";

    leftInfo->setStyleSheet(infoStyle);
    forwardInfo->setStyleSheet(infoStyle);
    rightInfo->setStyleSheet(infoStyle);

    QString twoPassengersProb, twoCarsProb, manProb,
            oneCarProb, onePassengerProb;

    QString leftDescr = "Лобовое столкновение";
    QString forwardDescr = "Наезд на пешехода";
    QString rightDescr = "Вылет в кювет";

    for (int i = 0; i < this->test.size() && !finished; i++) {
        leftInfo->hide();
        forwardInfo->hide();
        rightInfo->hide();

        leftInfo->clear();
        forwardInfo->clear();
        rightInfo->clear();

        leftInfo->move(255, 270);
        forwardInfo->move(490, 220);
        rightInfo->move(680, 270);

        twoPassengersProb = "Смерть 2 пассажиров – " +
                QString::number(this->test[i].table[0]);
        twoCarsProb = "Уничтожение 2 машин – " +
                QString::number(this->test[i].table[1]);
        manProb = "Смерть пешехода – " +
                QString::number(this->test[i].table[2]);
        onePassengerProb = "Смерть пассажира – " +
                QString::number(this->test[i].table[3]);
        oneCarProb = "Уничтожение машины – " +
                QString::number(this->test[i].table[4]);

        leftInfo->setText("<u>" + leftDescr + "</u><br>"+
                          twoPassengersProb + "<br>" +
                                twoCarsProb);
        forwardInfo->setText("<u>" + forwardDescr + "</u><br>" +
                                manProb);
        rightInfo->setText("<u>" + rightDescr + "</u><br>" +
                                onePassengerProb + "<br>" +
                                oneCarProb);

        ui->leftButton->hide();
        ui->forwardButton->hide();
        ui->rightButton->hide();
        ui->altButton->hide();
        ui->pictLabel->hide();
        this->pictOn = false;
        this->spacePressed = false;

        left->move(500, 285);
        forward->move(570, 270);
        right->move(630, 285);//285
        leftNumber->move(520, 330);
        forwardNumber->move(590, 300);
        rightNumber->move(620, 330);

        left->hide();
        right->hide();
        forward->hide();
        leftNumber->hide();
        forwardNumber->hide();
        rightNumber->hide();

        car->move(550, 800);//430
        carOncoming->move(320, -350);
        man->move(800, 50);

        this->animationOn = true;
        this->group.clear();
        QPropertyAnimation *animationCar =
                new QPropertyAnimation(car, "pos");
        animationCar->setDuration(this->duration);
        animationCar->setStartValue(QPoint(550, 800));
        animationCar->setEndValue(QPoint(550, 330));
        this->group.addAnimation(animationCar);
        QPropertyAnimation *animationCarOncoming =
                new QPropertyAnimation(carOncoming, "pos");
        animationCarOncoming->setDuration(this->duration);
        animationCarOncoming->setStartValue(QPoint(320, -350));
        animationCarOncoming->setEndValue(QPoint(320, -50));
        this->group.addAnimation(animationCarOncoming);
        QPropertyAnimation *animationMan =
                new QPropertyAnimation(man, "pos");
        animationMan->setDuration(this->duration);
        animationMan->setStartValue(QPoint(700, 50));
        animationMan->setEndValue(QPoint(620, 50));
        this->group.addAnimation(animationMan);
        this->group.start();
        this->timer = new QTimer;
        this->timer->start(this->duration);
        QEventLoop loop_timer;
        connect(this->timer, SIGNAL(timeout()),
                &loop_timer, SLOT(quit()));
        loop_timer.exec();
        this->animationOn = false;

        leftInfo->show();
        forwardInfo->show();
        rightInfo->show();

        ui->leftButton->show();
        ui->forwardButton->show();
        ui->rightButton->show();
        ui->altButton->show();

        left->show();
        right->show();
        forward->show();
        leftNumber->setText("1");
        leftNumber->show();
        forwardNumber->setText("2");
        forwardNumber->show();
        rightNumber->setText("3");
        rightNumber->show();

        this->pictInfo = this->test[i].showPict;

        this->timeSpent = new QTime;
        this->timeSpentSaved = 0;
        this->timeSpent->start();
        QEventLoop loop_key;
        connect(this, SIGNAL(keyPressed()),
                &loop_key, SLOT(quit()));
        loop_key.exec();

        if (this->spacePressed) {
            leftInfo->hide();
            forwardInfo->hide();
            rightInfo->hide();

            leftInfo->clear();
            forwardInfo->clear();
            rightInfo->clear();

            leftInfo->move(255, 190);
            forwardInfo->move(490, 138);
            rightInfo->move(680, 190);

            twoPassengersProb = "Смерть 2 пассажиров – " +
                    QString::number(this->test[i].tableAlt[0]);
            twoCarsProb = "Уничтожение 2 машин – " +
                    QString::number(this->test[i].tableAlt[1]);
            manProb = "Смерть пешехода – " +
                    QString::number(this->test[i].tableAlt[2]);
            onePassengerProb = "Смерть пассажира – " +
                    QString::number(this->test[i].tableAlt[3]);
            oneCarProb = "Уничтожение машины – " +
                    QString::number(this->test[i].tableAlt[4]);

            leftInfo->setText("<u>" + leftDescr + "</u><br>"+
                              twoPassengersProb + "<br>" +
                                    twoCarsProb);
            forwardInfo->setText("<u>" + forwardDescr + "</u><br>" +
                                    manProb);
            rightInfo->setText("<u>" + rightDescr + "</u><br>" +
                                    onePassengerProb + "<br>" +
                                    oneCarProb);

            ui->leftButton->hide();
            ui->forwardButton->hide();
            ui->rightButton->hide();
            ui->altButton->hide();

            left->hide();
            right->hide();
            forward->hide();
            leftNumber->hide();
            forwardNumber->hide();
            rightNumber->hide();

            this->animationOn = true;
            this->group.clear();
            QPropertyAnimation *animationCar =
                    new QPropertyAnimation(car, "pos");
            animationCar->setDuration(this->durationAlt);
            animationCar->setStartValue(QPoint(550, 330));
            animationCar->setEndValue(QPoint(550, 240));
            this->group.addAnimation(animationCar);
            QPropertyAnimation *animationCarOncoming =
                    new QPropertyAnimation(carOncoming, "pos");
            animationCarOncoming->setDuration(this->durationAlt);
            animationCarOncoming->setStartValue(QPoint(320, -50));
            animationCarOncoming->setEndValue(QPoint(320, 0));
            this->group.addAnimation(animationCarOncoming);
            QPropertyAnimation *animationMan =
                    new QPropertyAnimation(man, "pos");
            animationMan->setDuration(this->durationAlt);
            animationMan->setStartValue(QPoint(620, 50));
            animationMan->setEndValue(QPoint(550, 50));
            this->group.addAnimation(animationMan);
            this->group.start();

            this->timer = new QTimer;
            this->timer->start(this->durationAlt);
            QEventLoop loop_timer;
            connect(this->timer, SIGNAL(timeout()),
                    &loop_timer, SLOT(quit()));
            loop_timer.exec();

            this->animationOn = false;

            left->move(500, 195);
            forward->move(570, 183);
            right->move(630, 195);//285
            leftNumber->move(520, 240);
            forwardNumber->move(590, 213);
            rightNumber->move(620, 240);

            ui->leftButton->show();
            ui->forwardButton->show();
            ui->rightButton->show();

            left->show();
            right->show();
            forward->show();
            leftNumber->setText("1");
            leftNumber->show();
            forwardNumber->setText("2");
            forwardNumber->show();
            rightNumber->setText("3");
            rightNumber->show();

            leftInfo->show();
            forwardInfo->show();
            rightInfo->show();

            this->pictInfo = this->test[i].showPictAlt;

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
    QString fileName = "results.csv";
    QFile file(fileName);
    if (!file.exists())
        file.open(QIODevice::WriteOnly);
    else
        file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << this->userName_ << ','
        << QDateTime::currentDateTime().toString("dd.MM.yyyy") << ','
        << QTime::currentTime().toString("hh:mm");
    for (auto ans : this->answers)
        out << ',' << ans;
    out << '\n';
    file.close();
}

void Quiz::onButtonClicked(int button)
{
    if (this->animationOn)
        return;
    if (this->isPaused)
        return;
    if (this->spacePressed && button == 4)
        return;
    if (!this->spacePressed && button == 4) {
        this->spacePressed = true;
        this->timeSpentSavedSpace = this->timeSpentSaved +
                this->timeSpent->elapsed();
        emit keyPressed();
        return;
    }
    Answer userAnswer;
    if (this->spacePressed) {
        userAnswer.timeSpent = this->timeSpentSavedSpace;
        userAnswer.directionChosen = Answer::direction::alt;
        userAnswer.timeSpentAlt = this->timeSpentSaved +
                this->timeSpent->elapsed();
        if (button == 1) {
            userAnswer.directionChosenAlt = Answer::direction::left;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
        } else if (button == 2) {
            userAnswer.directionChosenAlt = Answer::direction::forward;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
            userAnswer.directionChosenAlt = Answer::direction::right;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
    } else {
        userAnswer.timeSpent = this->timeSpentSaved +
                this->timeSpent->elapsed();
        if (button == 1) {
            userAnswer.directionChosen = Answer::direction::left;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
        } else if (button == 2) {
            userAnswer.directionChosen = Answer::direction::forward;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
            userAnswer.directionChosen = Answer::direction::right;

            if (this->pictInfo == 1) {
                this->pictOn = true;
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
    this->quizTimer->start();
}

void Quiz::setPlay()
{
    ui->pauseButton->setStyleSheet("border-image:url("
                                   "://pictures/play.png)");
    this->quizTimer->stop();
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

void Quiz::on_leftButton_clicked()
{
    emit buttonClicked(1);
}

void Quiz::on_forwardButton_clicked()
{
    emit buttonClicked(2);
}

void Quiz::on_rightButton_clicked()
{
    emit buttonClicked(3);
}

void Quiz::on_altButton_clicked()
{
    emit buttonClicked(4);
}

void Quiz::updateQuizTimer()
{
    this->quizTime = quizTime.addSecs(-1);
    ui->countLabel->setText(this->quizTime.toString("m:ss"));
    if (this->quizTime.toString("m:ss") == "0:00") {
        this->finished = true;
        this->quizTimer->stop();
    }
}
