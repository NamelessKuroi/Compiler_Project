#include "qmemo.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QPoint>
#include <QTextStream>
#include <QCloseEvent>
#include <QToolBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QMenuBar>
#include <QApplication>
#include <QStatusBar>
#include <QStringList>
#include <QtGui>
#include <QIcon>

#include "class/lexer/SourceStream.h"
#include "class/common/Token.h"
#include "class/semantic/Checker.h"
#include "class/code-generator/encoder.h"
#include "console.h"
#include "class/interpreter/memo-compiler.h"
#include "class/interpreter/interpreter.h"
#include "class/ast/tree.h"




QMemo::QMemo(QWidget *parent)
    : QMainWindow(parent) ,completer(0)
{
    setupUi();

    diropen = "";

    readSettings();
    setCurrentFile("");
    createConnections();

    setWindowIcon(QIcon(":/images/mozilla.png"));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    setMaximumSize(640, 480);
    setMinimumSize(560, 400);

    setWindowTitle(tr("Memo Compiler[*]"));
}

void QMemo::setupUi()
{
    createMenus();

    QTabWidget * mainWidget = new QTabWidget(0);
    setCentralWidget(mainWidget);

    QWidget *widget = new QWidget;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    widget->setLayout(verticalLayout);
    verticalLayout->addWidget(sourceTextEdit = new CodeEditor());

    //plus
    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    sourceTextEdit->setCompleter(completer);
    //plus

    verticalLayout->addWidget(new QLabel(tr("Console")));
    connect(sourceTextEdit->document(), SIGNAL(contentsChanged()),this, SLOT(documentWasModified()));

    Console::instance()->console()->setFixedHeight(100);
    verticalLayout->addWidget(Console::instance()->console());

    mainWidget->addTab(widget, tr("Source"));
    mainWidget->addTab(lexerTextEdit = new QTextEdit(mainWidget), tr("Lexer Output"));
    mainWidget->addTab(symbolTableTextEdit = new QTextEdit(mainWidget), tr("Symbol Table"));
    highlighter = new Highlighter( sourceTextEdit->document());

    astTreeWidget = new QTreeWidget();
    astTreeWidget->setHeaderLabel(tr("ARBOL DE SINTAXIS ABSTRACTA"));

    mainWidget->addTab(astTreeWidget, tr("AST"));


}

void QMemo::examineChildElements( Data * value ,
                          QTreeWidgetItem *parentItem)
{
    QList<Data * > * h = value->getHijos();
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    if( ! value->Eshoja())
    item->setIcon(0 , QIcon(":/images/open.png"));
    else
    item->setIcon(0 , QIcon(":/images/docs.png"));

    item->setText(0,value->getRoot());
    parentItem->addChild(item);

    if ( !value->Eshoja() )
    {
        for(int i = 0 ; i < h->size();i++)
        {
            examineChildElements(h->value(i),item);
        }
    }


}
void QMemo::CrearArbol()
{

//------------------------------------ASTEXPRANK----------------------------------//


    QList<Data * >  * ASTIDENTIFIERDATA = new QList<Data*>();
    ASTIDENTIFIERDATA->append(new Data(tr("ASTIdentifierDeclaration"),new QList<Data*>() ) );
    ASTIDENTIFIERDATA->append(new Data(tr("ASTIdentifierReference"),new QList<Data*>() ) );
    ASTIDENTIFIERDATA->append(new Data(tr("ASTIdentifierValue "),new QList<Data*>() ) );


    QList<Data * >  * ASTSYMBOLDATA = new QList<Data*>();
    ASTSYMBOLDATA->append( new Data( tr("ASTIntValue") , new QList<Data*>() ) );
    ASTSYMBOLDATA->append( new Data( tr("ASTIdentifier") , ASTIDENTIFIERDATA ) );

    QList<Data * >  * ASTOPERATORBIBINARYDATA = new QList<Data*>();
    ASTOPERATORBIBINARYDATA->append(new Data(tr("ASTUnion"),new QList<Data*>() ) );
    ASTOPERATORBIBINARYDATA->append(new Data(tr("ASTInterception"),new QList<Data*>() ) );
    ASTOPERATORBIBINARYDATA->append(new Data(tr("ASTDifference"),new QList<Data*>() ) );


    QList<Data * >  * ASTEXPRANKDATA = new QList<Data*>();
    ASTEXPRANKDATA->append( new Data( tr("ASTOperatorBinary") , ASTOPERATORBIBINARYDATA ) );
    ASTEXPRANKDATA->append( new Data( tr("ASTSymbol") , ASTSYMBOLDATA ) );
  //------------------------------------ASTEXPRANK----------------------------------//

  //------------------------------------ASTPROGRAMA----------------------------------//
    //ASTAssignation
    QList<Data * >  * ASTASSIGNATIONDATA = new QList<Data*>();
    ASTASSIGNATIONDATA->append(new Data(tr("ASTInitInt"),new QList<Data*>() ) );
    ASTASSIGNATIONDATA->append(new Data(tr("ASTInitRank"),new QList<Data*>() ) );
    ASTASSIGNATIONDATA->append(new Data(tr("ASTInitRankExp"),new QList<Data*>() ) );

    //ASTInstruction
     QList<Data * >  * ASTINSTRUCTIONDATA = new QList<Data*>();
     ASTINSTRUCTIONDATA->append(new Data(tr("ASTDeclaration"),new QList<Data*>() ) );
     ASTINSTRUCTIONDATA->append(new Data(tr("ASTAssignation"),ASTASSIGNATIONDATA ) );
     ASTINSTRUCTIONDATA->append(new Data(tr("ASTPrint"),new QList<Data*>() ) );

    //ASTPrograma
    QList<Data * >  * ASTPROGRAMDATA = new QList<Data*>();
    ASTPROGRAMDATA->append(new Data(tr("ASTInstruction"),ASTINSTRUCTIONDATA ) );
  //------------------------------------ASTPROGRAMA----------------------------------//
    //AST
    QList<Data * >  * ASTDATA = new QList<Data*>();
    ASTDATA->append( new Data( tr("ASTProgram") , ASTPROGRAMDATA ) );
    ASTDATA->append( new Data( tr("ASTExpRAnk") , ASTEXPRANKDATA ) );



    arbol = new Data(tr("AST"), ASTDATA);
}

void QMemo::createMenus()
{
    // File Menu
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));

    // Standar Toolbar
    QToolBar *toolBar = addToolBar(tr("toolBar"));

    // file menu actions
    newAction = new QAction(QIcon(":/images/new.png"), tr("New"), fileMenu);
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    fileMenu->addAction(newAction);
    toolBar->addAction(newAction);

    openAction = new QAction(QIcon(":/images/open.png"), tr("Open"), fileMenu);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    toolBar->addAction(openAction);

    saveAction = new QAction(QIcon(":/images/save.png"), tr("Save"), fileMenu);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    toolBar->addAction(saveAction);

    closeAction = new QAction(QIcon(":/images/exit.png"), tr("Close"), fileMenu);
    closeAction->setShortcut(QKeySequence("Alt+F4"));
    fileMenu->addAction(closeAction);

    // Run Menu
    QMenu *runMenu = menuBar()->addMenu(tr("Run"));
    runAction = new QAction(QIcon(":/images/run.png"), tr("Run"), runMenu);
    runAction->setShortcut(Qt::Key_F5);
    runMenu->addAction(runAction);
    toolBar->addAction(runAction);

    // Help Menu
    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpAction = new QAction(QIcon(":/images/help.png"), tr("About QMemo"), helpMenu);
    helpAction->setShortcut(Qt::Key_F1);
    helpMenu->addAction(helpAction);
}

QMemo::~QMemo()
{
}

void QMemo::createConnections()
{
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(runAction, SIGNAL(triggered()), this, SLOT(BuildExecute()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(about()));
}

bool QMemo::maybeSave()
{
    if (sourceTextEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("QMemo"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool QMemo::save()
{
    if (diropen.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(diropen);
    }
}

bool QMemo::saveAs()
{
    QString filter("*.txt");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), filter);

    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool QMemo::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, windowTitle(),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << sourceTextEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void QMemo::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QMemo::setCurrentFile(const QString &fileName)
{
    diropen = fileName;
    sourceTextEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = diropen;
    if (diropen.isEmpty())
        shownName = "untitled.txt";

    setWindowFilePath(shownName);
}

void QMemo::readSettings()
{
    QSettings settings("Trolltech", "QMemo");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void QMemo::writeSettings()
{
    QSettings settings("Trolltech", "QMemo");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void QMemo::newFile()
{
    if (maybeSave())
    {
        sourceTextEdit->clear();
        Console::instance()->console()->clear();
        lexerTextEdit->clear();
        symbolTableTextEdit->clear();
        setCurrentFile("");
    }
}

void QMemo::open()
{
    if (maybeSave())
    {
        QString filter("*.txt");
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), filter);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

void QMemo::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, windowTitle(),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    sourceTextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void QMemo::documentWasModified()
{
    setWindowModified(sourceTextEdit->document()->isModified());
}

void QMemo::about()
{
    QMessageBox::about(this, windowTitle(),
                       tr("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
}

void QMemo::BuildExecute()
{
    save();
    if (diropen != "")
    {
        // salida del analizador lexico
         MakeLexerOutput();

        // inicialización
       datos = sourceTextEdit->toPlainText();
       SourceStream *source = new SourceStream(datos);

        // proceso de interpretación
        Console::instance()->console()->clear();


        MemoCompiler *  compiler = new MemoCompiler(source);
        QList<RuntimeEntity*> code = compiler->Compile();


        Interpreter *program = new Interpreter(code);
        program->Execute();

        // tree widget for AST

        AST * temp = compiler->getAST();
        astTreeWidget->clear();
        astTreeWidget->setAnimated(true);
        Visitor * Examinador = new Tree(astTreeWidget,compiler->getST() );
        temp->visit(Examinador);

    }
}

void QMemo::MakeLexerOutput()
{
    QFile file(diropen);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("QMemo"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(diropen)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    datos = in.readAll();
    SourceStream * source = new SourceStream(datos);
    SymbolsTable * table = new SymbolsTable();
    ErrorReporter *errorList = new ErrorReporter();
    MemoLexicalAnalyzer *myLexer = new MemoLexicalAnalyzer(source, table, errorList);

    //lexerTextEdit->clear();
    Token * currentToken = myLexer->NextToken();
    QString stringLine = "";
    int currentLine = currentToken->GetLine();
    int lastLine = currentLine;

    while(currentToken->GetKind() != tk_EOF )
    {
        if( lastLine == currentLine )
        {
            stringLine += currentToken->ToString();
        }
        else
        {
            lexerTextEdit->append(stringLine);
            stringLine = currentToken->ToString();
        }

        lastLine = currentLine;
        currentToken = myLexer->NextToken();
        currentLine  = currentToken->GetLine();
    }

    lexerTextEdit->append(stringLine);
    MakeSymbolTableOutput(table);

    delete table;
    delete myLexer;
    delete source;

}

void QMemo::MakeSymbolTableOutput(SymbolsTable *table)
{
    int i = 0;
    symbolTableTextEdit->clear();
    while(i < table->Count())
    {
        symbolTableTextEdit->append(table->Entry(i)->ToString());
        i++;
    }
}
//plus

QAbstractItemModel * QMemo::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, completer);

}

