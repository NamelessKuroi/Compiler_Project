#include "qmemo.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(customcompleter);

    QApplication a(argc, argv);
    QMemo w;
    w.show();
    return a.exec();
}
