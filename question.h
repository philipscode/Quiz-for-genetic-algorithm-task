#ifndef QUESTION_H
#define QUESTION_H

#include <QTextStream>
#include <QVector>
#include <QString>

struct ProbCost
{
    double prob, cost;
};

struct Question
{
    Question();
    QVector<QVector<ProbCost>> table;
    QVector<QVector<ProbCost>> tableAlt;
    QVector<int> showPict, showPictAlt;
    friend QTextStream& operator >> (QTextStream&, Question&);
};

#endif // QUESTION_H
