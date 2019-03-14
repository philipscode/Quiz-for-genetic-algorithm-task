#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QByteArray>
#include <vector>

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
                  QString name = "default", QString surname = "name");
    ~Quiz();
    void doTest();
    void saveAnswers() const;

signals:
    void keyPressed();

    void keyPressedAlt();

private slots:
    void onKeyPressed(int);

    void on_pauseButton_clicked();

private:
    void setPlay();
    void setPause();
    Ui::Quiz *ui;
    QList<Question> test;
    QList<Answer> answers;
    QString name_, surname_;
    QTime *timeSpent;
    bool animationOn;
    bool isPaused;
    bool spacePressed;
    bool pictOn;
    QParallelAnimationGroup group;
    QTimer *timer;
    int timerSaved;
    int timeSpentSaved;
    int duration;
    int durationAlt;
    int durationPict;
    std::vector<int> pictInfo {0, 0, 0};
    std::vector<int> numbers {0, 0, 0};
    QPixmap leftLow {"://pictures/left_low.jpg"};
    QPixmap leftMedium {"://pictures/left_medium.jpg"};
    QPixmap leftHigh {"://pictures/left_high.jpg"};
    QPixmap forwardMeduim {"://pictures/forward_medium.jpg"};
    QPixmap forwardHigh {"://pictures/forward_high.jpg"};
    QPixmap rightLow {"://pictures/right_low.jpg"};
    QPixmap rightMedium {"://pictures/right_medium.jpg"};
    QPixmap rightHigh {"://pictures/right_high.jpg"};
    QString leftLowInfo, leftMediumInfo, leftHighInfo;
    QString forwardLowInfo, forwardMediumInfo, forwardHighInfo;
    QString rightLowInfo, rightMediumInfo, rightHighInfo;
};

#endif // QUIZ_H
