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
        printf("File not found or empty!");
        system("pause");

        return 0;
    }

    cleanSource(source);

    uint    practicalGlobalCalls = 0,  // Aup
            availableGlobalCalls = 0;   // Pup

    countGlobalVars(source, practicalGlobalCalls, availableGlobalCalls);


    result += QString("\n[Aup/Pup]: %1/%2\n\n").arg(practicalGlobalCalls).arg(availableGlobalCalls);
    result += "Rup = ";

    if (availableGlobalCalls != 0)
    {
        result += (QString::number( (float)practicalGlobalCalls/availableGlobalCalls, 'g', 10) );
    }
    else
    {
        result += "N/A";
    }

    result += "\n\n";

    writeResult(result, "output.txt");
    system("pause");

    return 0;
}
