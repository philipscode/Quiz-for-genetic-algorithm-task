#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPixmap>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QByteArray>
#include <QHeaderView>
#include <QVector>

#include "question.h"
#include "answer.h"

namespace Ui {
class Quiz;
}

class Quiz : public QWidget
{
    Q_OBJECT

public:
    explicit Quiz(QWidget *parent = nullptr,
                  QString userName = "default name");
    ~Quiz();
    void doTest();
    void saveAnswers() const;

signals:
    void buttonClicked(int);

    void keyPressed();

    void keyPressedAlt();

private slots:
    void onButtonClicked(int);

    void on_pauseButton_clicked();

    void on_leftButton_clicked();

    void on_forwardButton_clicked();

    void on_rightButton_clicked();

    void on_altButton_clicked();

    void updateQuizTimer();

private:
    void setPlay();
    void setPause();

    Ui::Quiz *ui;
    QList<Question> test;
    QList<Answer> answers;
    QString userName_;
    QTime *timeSpent;
    bool animationOn;
    bool isPaused;
    bool spacePressed;
    bool pictOn;
    QParallelAnimationGroup group;
    QTimer *timer;
    int timerSaved;
    int timeSpentSaved;
    int timeSpentSavedSpace;
    int duration;
    int durationAlt;
    int durationPict;
    int pictInfo;
    QPixmap leftHigh {"://pictures/left_high.jpg"};
    QPixmap forwardHigh {"://pictures/forward_high.jpg"};
    QPixmap rightHigh {"://pictures/right_high.jpg"};
    QTimer *quizTimer;
    QTime quizTime;
    bool finished;
};

#endif // QUIZ_H
