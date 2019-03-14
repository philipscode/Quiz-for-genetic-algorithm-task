#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QTextStream>

class Question
{
public:
    Question();
    Question(int, int, int,
             int, int, int,
             int, int, int,
             int, int, int);
    int getLeft() const;
    int getForward() const;
    int getRight() const;
    int getLeftPict() const;
    int getForwardPict() const;
    int getRightPict() const;
    int getLeftAlt() const;
    int getForwardAlt() const;
    int getRightAlt() const;
    int getLeftPictAlt() const;
    int getForwardPictAlt() const;
    int getRightPictAlt() const;
    friend QTextStream& operator >> (QTextStream&, Question&);
private:
    int left_, forward_, right_;
    int leftPict_, forwardPict_, rightPict_;
    int leftAlt_, forwardAlt_, rightAlt_;
    int leftPictAlt_, forwardPictAlt_, rightPictAlt_;
};

#endif // QUESTION_H
