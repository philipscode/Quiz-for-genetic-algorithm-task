#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QTextStream>

class Question
{
public:
    Question();
    Question(QString, int, int, int);
    QString getImagePath() const;
    int getLeft() const;
    int getForward() const;
    int getRight() const;
    friend QTextStream& operator >> (QTextStream&, Question&);
private:
    QString imagePath_;
    int leftChoice_, forwardChoice_, rightChoice_;
};

#endif // QUESTION_H
