
#ifndef ERRORREPORTER_H_
#define ERRORREPORTER_H_

#include <QString>
#include <QList>

#include "SourcePosition.h"

class CompilerError
{
    private:
        QString text;
        int line;
    public:
        CompilerError(QString text, int line)
        {
            this->text = text;
            this->line = line;
        }

        int GetLine()
        {
            return line;
        }

        QString GetText()
        {
            return text +"  (Line: "+QString::number(line)+ (QString)')';
        }
};

class ErrorReporter
{
    private:
        QList<CompilerError*> *errors;
    public:
        ErrorReporter();
        void AddError(CompilerError* error);
        CompilerError* GetError(int posError);
        int Count();
        ~ErrorReporter();
};

#endif /* ERRORREPORTER_H_ */
