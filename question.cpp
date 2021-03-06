#include "question.h"

Question::Question()
{
    table.fill(0, 5);
    tableAlt.fill(0, 5);
    showPict = 0;
    showPictAlt = 0;
}

QTextStream& operator >> (QTextStream &in, Question &q)
{
    QString tmp;
    for (int i = 0; i < 5; i++) {
        double sample;
        in >> tmp;
        sample = tmp.toDouble();
        q.table[i] = sample;
    }
    in >> tmp;
    q.showPict = tmp.toInt();
    for (int i = 0; i < 5; i++) {
        double sample;
        in >> tmp;
        sample = tmp.toDouble();
        q.tableAlt[i] = sample;
    }
    in >> tmp;
    q.showPictAlt = tmp.toInt();
    return in;
}
