
#include "ErrorReporter.h"

ErrorReporter::ErrorReporter()
{
    errors = new QList<CompilerError*>();
}

void ErrorReporter::AddError(CompilerError* error)
{
    errors->append(error);
}

CompilerError* ErrorReporter::GetError(int posError)
{
    return errors->value(posError);
}

int ErrorReporter::Count()
{
    return errors->size();
}

ErrorReporter::~ErrorReporter()
{
    delete errors;
}

