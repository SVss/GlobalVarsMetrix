#include "file_work.h"
#include "stuff.h"

int main(int argc, char *argv[])
{
    QString inputFileName = "input.pas";
    if (argc > 1)
        inputFileName = argv[1];

    QString result = QString("\nResults for file: \"%1\"\n").arg(getRelativeFileName(inputFileName) );

    QString source = readSource(inputFileName);

    if (source.isEmpty() )
    {
        printf("File not found!");
        system("pause");
        return 0;
    }

    cleanSource(source);

    uint    practicalGlobalCalls = 0,  // Aup
            availableGlobalCalls = 0;   // Pup

    countGlobalVars(source, practicalGlobalCalls, availableGlobalCalls);


    result += QString("\n[Aup/Pup]: %1/%2\n\nRup = %3").
            arg(practicalGlobalCalls).arg(availableGlobalCalls).
            arg(QString::number( (float)practicalGlobalCalls/availableGlobalCalls, 'g', 10) );

    writeResult(result, "output.txt");
    system("pause");
    return 0;
}
