#include "question.h"

Question::Question() :
    left_(0), forward_(0), right_(0),
    leftPict_(0), forwardPict_(0), rightPict_(0),
    leftAlt_(0), forwardAlt_(0), rightAlt_(0),
    leftPictAlt_(0), forwardPictAlt_(0), rightPictAlt_(0)
{
}

Question::Question(int left, int forward, int right,
                   int leftPict, int forwardPict, int rightPict,
                   int leftAlt, int forwardAlt, int rightAlt,
                   int leftPictAlt, int forwardPictAlt,
                   int rightPictAlt) :
   left_(left), forward_(forward), right_(right),
   leftPict_(leftPict), forwardPict_(forwardPict),
   rightPict_(rightPict), leftAlt_(leftAlt),
   forwardAlt_(forwardAlt), rightAlt_(rightAlt),
   leftPictAlt_(leftPictAlt), forwardPictAlt_(forwardPictAlt),
   rightPictAlt_(rightPictAlt)
{
}

int Question::getLeft() const
{
    return left_;
}

int Question::getForward() const
{
    return forward_;
}

int Question::getRight() const
{
    return right_;
}

int Question::getLeftPict() const
{
    return leftPict_;
}

int Question::getForwardPict() const
{
    return forwardPict_;
}

int Question::getRightPict() const
{
    return rightPict_;
}

int Question::getLeftAlt() const
{
    return leftAlt_;
}

int Question::getForwardAlt() const
{
    return forwardAlt_;
}

int Question::getRightAlt() const
{
    return rightAlt_;
}

int Question::getLeftPictAlt() const
{
    return leftPictAlt_;
}

int Question::getForwardPictAlt() const
{
    return forwardPictAlt_;
}

int Question::getRightPictAlt() const
{
    return rightPictAlt_;
}

QTextStream& operator >> (QTextStream &in, Question &q)
{
    int left, forward, right;
    int leftPict, forwardPict, rightPict;
    int leftAlt, forwardAlt, rightAlt;
    int leftPictAlt, forwardPictAlt, rightPictAlt;
    in >> left >> forward >> right >>
            leftPict >> forwardPict >> rightPict >>
            leftAlt >> forwardAlt >> rightAlt >>
            leftPictAlt >> forwardPictAlt >> rightPictAlt;
    q = Question(left, forward, right,
                 leftPict, forwardPict, rightPict,
                 leftAlt, forwardAlt, rightAlt,
                 leftPictAlt, forwardPictAlt, rightPictAlt);
    return in;
}
