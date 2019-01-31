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
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include "question.h"

struct answer
{
    enum direction { left, forward, right };
};

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
    void doTest() const;
    void saveAnswers() const;

signals:
    void keyPressed();

private slots:
    void onKeyPressed(int);

private:
    Ui::Quiz *ui;
    QList<Question> test;
    QList<answer::direction> answers;
    QString name_, surname_;
};

#endif // QUIZ_H
