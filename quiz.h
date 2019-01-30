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
#include "question.h"

namespace Ui {
class Quiz;
}

class Quiz : public QWidget
{
    Q_OBJECT

public:
    explicit Quiz(QWidget *parent = nullptr);
    ~Quiz();
    void doTest() const;

signals:
    void keyPressed();

private slots:
    void onKeyPressed();

private:
    Ui::Quiz *ui;
    QList<Question> test;
};

#endif // QUIZ_H
