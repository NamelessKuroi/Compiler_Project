#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>

// singleton for Console
class Console
{
    public:
       static Console* instance()
       {
           if (m_instance == 0)
           {
               m_instance = new Console;
               m_console = new QTextEdit;
           }

           return m_instance;
       }

       QTextEdit *console()  {  return m_console;  }

       void clear()   {   m_console->clear();  }

       void print(QString s)
       {
           m_console->append(s);

       }

       void println(QString s)
       {
           m_console->append(s + "\n");
       }

       void print(int v)
       {
           m_console->append(QString::number(v));
       }

       void println(int v)
       {
           m_console->append(QString::number(v) + "\n");
       }

       void print(float f)
       {
           m_console->append(QString::number(f) + "\n");
       }

       void println(float v)
       {
           m_console->append(QString::number(v) + "\n");
       }

    private:
       Console() { }
       static Console* m_instance;
       static QTextEdit *m_console;
};

#endif // CONSOLE_H
