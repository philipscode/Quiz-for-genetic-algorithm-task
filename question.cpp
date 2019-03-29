#include "question.h"

Question::Question()
{
    ProbCost tmp;
    tmp.prob = tmp.cost = 0.0;
    QVector<ProbCost> vec;
    vec.fill(tmp, 4);
    table.fill(vec, 3);
    tableAlt.fill(vec, 4);
    showPict.fill(0, 3);
    showPictAlt.fill(0, 3);
}

QTextStream& operator >> (QTextStream &in, Question &q)
{
    QString tmp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++) {
            ProbCost sample;
            in >> tmp;
            sample.prob = tmp.toDouble();
            in >> tmp;
            sample.cost = tmp.toDouble();
            q.table[i][j] = sample;
        }
    for (int i = 0; i < 3; i++) {
        int num;
        in >> tmp;
        num = tmp.toInt();
        q.showPict[i] = num;
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++) {
            ProbCost sample;
            in >> tmp;
            sample.prob = tmp.toDouble();
            in >> tmp;
            sample.cost = tmp.toDouble();
            q.tableAlt[i][j] = sample;
        }
    for (int i = 0; i < 3; i++) {
        int num;
        in >> tmp;
        num = tmp.toInt();
        q.showPictAlt[i] = num;
    }
    return in;
}
