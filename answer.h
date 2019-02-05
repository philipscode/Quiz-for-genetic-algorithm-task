#ifndef ANSWER_H
#define ANSWER_H

#include <QTextStream>

struct Answer
{
    enum direction { left, forward, right };
    direction directionChosen;
    int timeSpent;
    friend QTextStream& operator << (QTextStream &out, Answer &ans)
    {
        out << ans.directionChosen << ' ' << ans.timeSpent << '\n';
        return out;
    }
};

#endif // ANSWER_H
