#include "memo-compiler.h"
#include "../../console.h"
#include "../semantic/Checker.h"
#include "../code-generator/encoder.h"

MemoCompiler::MemoCompiler(SourceStream *source)
{
    symbolsTable = new SymbolsTable;
    errorReporter = new ErrorReporter;
    scanner = new MemoLexicalAnalyzer(source, symbolsTable, errorReporter);
    parser = new MemoSyntacticAnalyzer(scanner, errorReporter);
    tree = NULL;
}

QList<RuntimeEntity*> MemoCompiler::Compile()
{
    // Análisis Sintáctico
    tree = parser->Parse();
    if (errorReporter->Count())
        ShowErrorOutput();
    else
    {
        // Análisis Semántico
        Visitor *checker = new Checker(symbolsTable, errorReporter);
        tree->visit(checker);

        if (errorReporter->Count())
            ShowErrorOutput();

        else
        {
            Console::instance()->println("Compilación satisfactoria.");
            Encoder* encoder = new Encoder(symbolsTable);
            tree->visit(encoder);
            return encoder->Code();
        }

    }

    return QList<RuntimeEntity*>();
}

void MemoCompiler::ShowErrorOutput()
{
    int i = 0;
    while(i < errorReporter->Count())
    {
        Console::instance()->console()->append(errorReporter->GetError(i)->GetText());
        i++;
    }
}

MemoCompiler::~MemoCompiler()
{
    if (scanner)
        delete scanner;

    if (errorReporter)
        delete errorReporter;

    if (symbolsTable)
        delete symbolsTable;

    if (parser)
        delete parser;

    if (tree)
        delete tree;
}
