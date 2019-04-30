#ifndef QUESTION_H
#define QUESTION_H

#include <QTextStream>
#include <QVector>
#include <QString>

struct Question
{
    Question();
    QVector<int> table, tableAlt;
    int showPict, showPictAlt;
    friend QTextStream& operator >> (QTextStream&, Question&);
};

#endif // QUESTION_H
