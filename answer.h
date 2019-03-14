#ifndef ANSWER_H
#define ANSWER_H

#include <QTextStream>

struct Answer
{
    enum direction { left, forward, right };

    int timeSpent;
    int isAlt;
    int pictShown;
    direction directionChosen;
    int number;
    friend QTextStream& operator << (QTextStream &out, Answer &ans)
    {
        out << ans.timeSpent << ' ' << ans.isAlt << ' ' <<
               ans.pictShown << ' ' << ans.directionChosen << ' ' <<
               ans.number;
        return out;
    }
};

#endif // ANSWER_H
