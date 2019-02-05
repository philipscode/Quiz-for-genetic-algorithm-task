#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPixmap>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
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
                  QString name = "", QString surname = "");
    ~Quiz();
    void doTest();
    void saveAnswers() const;

signals:
    void keyPressed();

private slots:
    void onKeyPressed(int);

private:
    Ui::Quiz *ui;
    QList<Question> test;
    QList<Answer> answers;
    QString name_, surname_;
    QTime *timeSpent;
};

#endif // QUIZ_H
