#ifndef ANSWER_H
#define ANSWER_H

#include <QTextStream>

struct Answer
{
    enum direction { left=1, forward, right, alt };

    int timeSpent;
    direction directionChosen;
    int timeSpentAlt = -1;
    direction directionChosenAlt;
    friend QTextStream& operator << (QTextStream &out, Answer &ans)
    {
        if (ans.timeSpentAlt == -1)
            out << ",," << ans.timeSpent << ','
                << ans.directionChosen;
        else
            out << ans.timeSpent << ',' << ans.directionChosen
                << ',' << ans.timeSpentAlt << ','
                << ans.directionChosenAlt;
        return out;
    }
};

#endif // ANSWER_H
