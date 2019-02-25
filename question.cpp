#include "question.h"

Question::Question() :
    objectType_(""), leftChoice_(0),
    forwardChoice_(0), rightChoice_(0)
{
}

Question::Question(QString objectType, int leftChoice,
                   int centralChoice, int rightChoice) :
   objectType_(objectType), leftChoice_(leftChoice),
   forwardChoice_(centralChoice), rightChoice_(rightChoice)
{
}

QString Question::getObjectType() const
{
    return objectType_;
}

int Question::getLeft() const
{
    return leftChoice_;
}

int Question::getForward() const
{
    return forwardChoice_;
}

int Question::getRight() const
{
    return rightChoice_;
}

QTextStream& operator >> (QTextStream &in, Question &q)
{
    QString imagePath;
    int leftChoice, centralChoice, rightChoice;
    in >> imagePath >> leftChoice >> centralChoice >> rightChoice;
    q = Question(imagePath, leftChoice,
                        centralChoice, rightChoice);
    return in;
}
