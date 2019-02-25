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
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
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

private slots:
    void onKeyPressed(int);

private:
    void setPlay();
    void setPause();
    Ui::Quiz *ui;
    QList<Question> test;
    QList<Answer> answers;
    QString name_, surname_;
    QTime *timeSpent;
    bool animationOn;
};

#endif // QUIZ_H
