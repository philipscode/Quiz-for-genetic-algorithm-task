#include "quiz.h"
#include "ui_quiz.h"
#include "answer.h"

#include <QDebug>

Quiz::Quiz(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::Quiz),
    userName_(userName), isPaused(false),
    duration(1000), durationAlt(1000), durationPict(1000)
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

    leftInfo = "Лобовое столкновение.";
    forwardInfo = "Наезд на пешехода.";
    rightInfo = "Вылет в кювет.";

    ui->table->setRowCount(4);
    ui->table->setColumnCount(3);

    QStringList horizontalLabels;
    horizontalLabels << tr("1") << tr("2") << tr("3");
    QStringList verticalLabels;
    verticalLabels << tr("Пешеход") << tr("Водитель") << tr("Машина") << tr("Встречная");

    ui->table->setHorizontalHeaderLabels(horizontalLabels);
    ui->table->setVerticalHeaderLabels(verticalLabels);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setFocusPolicy(Qt::NoFocus);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);

    connect(this, SIGNAL(buttonClicked(int)),
            this, SLOT(onButtonClicked(int)));
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

    QString infoStyle = "color: #db2b2b; font-size: 18px;"
                        "border: 2px solid #db2b2b; background-color: #e8b620";

    leftInfo->setStyleSheet(infoStyle);
    forwardInfo->setStyleSheet(infoStyle);
    rightInfo->setStyleSheet(infoStyle);

    leftInfo->setText(this->leftInfo);
    forwardInfo->setText(this->forwardInfo);
    rightInfo->setText(this->rightInfo);

    for (int i = 0; i < this->test.size(); i++) {
        ui->table->hide();
        ui->table->clearContents();

        ui->leftButton->hide();
        ui->forwardButton->hide();
        ui->rightButton->hide();
        ui->altButton->hide();

        ui->countLabel->setText(QString::number(i + 1) + " / " +
                                QString::number(this->test.size()));
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
        rightInfo->move(520, 350);

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

        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++)
                ui->table->setItem(k, j, new QTableWidgetItem(
                               QString::number(this->test[i].table[j][k].prob)
                           + " / " +
                           QString::number(this->test[i].table[j][k].cost)));
        ui->table->resizeRowsToContents();
        ui->table->show();

        leftInfo->show();
        forwardInfo->show();
        rightInfo->show();

        this->pictInfo = this->test[i].showPict;

        this->timeSpent = new QTime;
        this->timeSpentSaved = 0;
        this->timeSpent->start();
        QEventLoop loop_key;
        connect(this, SIGNAL(keyPressed()),
                &loop_key, SLOT(quit()));
        loop_key.exec();

        if (this->spacePressed) {
            ui->table->hide();
            ui->table->clearContents();

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

            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 4; k++)
                    ui->table->setItem(k, j, new QTableWidgetItem(
                                   QString::number(this->test[i].tableAlt[j][k].prob)
                               + " / " +
                               QString::number(this->test[i].tableAlt[j][k].cost)));

            ui->table->resizeRowsToContents();
            ui->table->show();

            leftInfo->move(120, 200);
            forwardInfo->move(500, 100);
            rightInfo->move(500, 270);

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
    /*QString dirName = QStandardPaths::writableLocation(
                QStandardPaths::DocumentsLocation) +
            QDir::separator() + "QUIZ_RESULTS" + QDir::separator();
    if (!QDir(dirName).exists())
        QDir().mkdir(dirName);*/
    QString fileName = "results.csv";
    QFile file(fileName);
    if (!file.exists())
        file.open(QIODevice::WriteOnly);
    else
        file.open(QIODevice::WriteOnly | QIODevice::Append);
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
        this->timeSpentSavedSpace = this->timeSpentSaved + this->timeSpent->elapsed();
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

            if (this->pictInfo[0] == 1) {
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

            if (this->pictInfo[1] == 1) {
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

            if (this->pictInfo[2] == 1) {
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

            if (this->pictInfo[0] == 1) {
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

            if (this->pictInfo[1] == 1) {
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

            if (this->pictInfo[2] == 1) {
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
