#include "quiz.h"
#include "ui_quiz.h"

Quiz::Quiz(QWidget *parent, QString name, QString surname) :
    QWidget(parent),
    ui(new Ui::Quiz),
    name_(name), surname_(surname)
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
    if (key == Qt::Key_Left)
        answers.append(answer::direction::left);
    else if (key == Qt::Key_Up)
        answers.append(answer::direction::forward);
    else
        answers.append(answer::direction::right);
    emit keyPressed();
}
