#ifndef SOURCESTREAM_H_
#define SOURCESTREAM_H_

#include <QFile>
#include <QString>
#include <QList>

class SourceStream
{
    private:
        int currentPosition;
        int currentLine;
        QString code;
    public:
        SourceStream(QString fileName);
        /*
            Devuelve el proximo caracter en el buffer de entrada
        */
        char Read();

        int CurrentPosition();

         /*
            Devuelve la linea actual
        */
         int CurrentLine();

};

#endif /* SOURCESTREAM_H_ */
