#include "quiz.h"
#include "ui_quiz.h"

#include <QDebug>

Quiz::Quiz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Quiz)
{
    ui->setupUi(this);
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
    for (int i = 0; i < test.size(); i++)
        qDebug() << test[i].getImagePath() << '\n'
                 << test[i].getLeft() << '\n'
                 << test[i].getCentral() << '\n'
                 << test[i].getRight() << '\n';
}

Quiz::~Quiz()
{
    delete ui;
}

void Quiz::doTest() const
{
    for (int i = 0; i < test.size(); i++) {
        QPixmap defaultPicture("://pictures/default.jpg");
        ui->pictureLabel->setPixmap(defaultPicture);
        ui->pictureLabel->setScaledContents(true);
        QTimer *timer = new QTimer;
        timer->start(3000);
        QEventLoop loop_1;
        connect(timer, SIGNAL(timeout()),
                &loop_1, SLOT(quit()));
        loop_1.exec();
        QPixmap picture(test[i].getImagePath());
        ui->pictureLabel->setPixmap(picture);
        ui->pictureLabel->setScaledContents(true);
        QEventLoop loop_2;
        connect(this, SIGNAL(keyPressed()),
                &loop_2, SLOT(quit()));
        loop_2.exec();
    }
    ui->pictureLabel->clear();
    ui->pictureLabel->setText("Тест пройден");
}

void Quiz::onKeyPressed()
{
    emit keyPressed();
}
