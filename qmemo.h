#ifndef QMEMO_H
#define QMEMO_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "class/lexer/LexicalAnalyzer.h"
#include "class/common/SymbolTable.h"
#include "class/lexer/ErrorReporter.h"
#include "class/lexer/MemoLexicalAnalyzer.h"
#include "class/parser/MemoSyntacticAnalyzer.h"
#include "highlighter.h"
#include "codeeditor.h"
#include "class/common/Data.h"
#include <QCompleter>


class QMemo : public QMainWindow
{
    Q_OBJECT

public:
    QMemo(QWidget *parent = 0);
    ~QMemo();
    void createConnections();

protected:
    void closeEvent(QCloseEvent *event);
    void setupUi();
    void createMenus();

private:
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void readSettings();
    void writeSettings();
    void loadFile(const QString &fileName);
    void examineChildElements( Data * value ,
                              QTreeWidgetItem * parentItem);

    QAbstractItemModel *modelFromFile(const QString& fileName);
    void CrearArbol();

protected:
    void MakeLexerOutput();
    void MakeSymbolTableOutput(SymbolsTable *table);

private slots:
    bool maybeSave();
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void documentWasModified();
    void about();
    void BuildExecute();

private:
    QString diropen;
    QString datos;
    Highlighter * highlighter;
    Data * arbol;

protected:
    // widgets
    CodeEditor *sourceTextEdit;
    QTextEdit *lexerTextEdit;
    QTextEdit *symbolTableTextEdit;
    QTreeWidget *astTreeWidget;
    QCompleter *completer;

    // actions
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *closeAction;
    QAction *runAction;
    QAction *helpAction;
};

#endif // QMEMO_H
