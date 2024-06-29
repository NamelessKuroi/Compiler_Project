TEMPLATE = app
TARGET = QMemo

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += class/common/Enum.h \
    class/common/SymbolTable.h \
    class/common/Token.h \
    class/lexer/Dictionary.h \
    class/lexer/ErrorReporter.h \
    class/lexer/LexicalAnalyzer.h \
    class/lexer/MemoLexicalAnalyzer.h \
    class/lexer/SourcePosition.h \
    class/lexer/SourceStream.h \
    class/parser/MemoSyntacticAnalyzer.h \
    class/parser/SyntacticAnalizer.h \    
    qmemo.h \
    class/common/visitor.h \
    class/code-generator/encoder.h \
    class/ast/AbstractSyntaxTree.h \
    class/semantic/Checker.h \
    class/runtime/context.h \
    class/runtime/memory.h \
    class/runtime/runtime-operator.h \
    console.h \
    class/interpreter/interpreter.h \
    class/interpreter/memo-compiler.h \
    highlighter.h \
    codeeditor.h \
    class/common/Data.h \
    class/ast/tree.h

SOURCES += class/common/SymbolTable.cpp \
    class/common/Token.cpp \
    class/lexer/Dictionary.cpp \
    class/lexer/ErrorReporter.cpp \
    class/lexer/LexicalAnalyzer.cpp \
    class/lexer/MemoLexicalAnalyzer.cpp \
    class/lexer/SourcePosition.cpp \
    class/lexer/SourceStream.cpp \
    class/parser/MemoSyntacticAnalyzer.cpp \
    class/parser/SyntacticAnalizer.cpp \
    qmemo.cpp \
    main.cpp \
    class/common/visitor.cpp \
    class/code-generator/encoder.cpp \
    class/ast/AbstractSyntaxTree.cpp \
    class/semantic/Checker.cpp \
    class/runtime/context.cpp \
    class/runtime/memory.cpp \
    class/runtime/runtime-operator.cpp \
    console.cpp \
    class/interpreter/interpreter.cpp \
    class/interpreter/memo-compiler.cpp \
    highlighter.cpp \
    codeeditor.cpp \
    class/ast/tree.cpp

RESOURCES += images.qrc \
    customcompleter.qrc

OTHER_FILES += \
    resources/wordlist.txt
