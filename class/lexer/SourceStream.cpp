#include "SourceStream.h"
#include <QMessageBox>
#include <QTextStream>

SourceStream::SourceStream(QString fileName)
{
	code = fileName;
    currentPosition = 0;
    currentLine = 1;
}

/*Devuelve la caracter actual en el Stream de caracteres*/
char SourceStream::Read()
{
    char letter;
    if(code!="")
    {
    	letter = code[0].toLatin1();
    	code = code.remove(0,1);
        currentPosition++;
        if(letter == '\n')
         currentLine++;
        return letter;
    }
    return 0;
}

/*Devuelve la posisción actual en el Stream de caracteres*/
int SourceStream::CurrentPosition()
{
    return currentPosition;
}

int SourceStream::CurrentLine()
{
     return currentLine;

}

