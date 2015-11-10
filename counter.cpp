#include "stuff.h"
#include "regexes.h"

#include <QStringList>

QStringList extractBlocksEx(QString &source)
{
    QStringList result;
    QRegularExpressionMatchIterator currMatchIter = RX_BLOCK.globalMatch(source);

    QString currBlock;
    while (currMatchIter.hasNext() )
    {
        currBlock = currMatchIter.next().captured(0).trimmed();
        cleanBlock(currBlock);

        result.append(currBlock);
    }

    source.replace(RX_BLOCK, BLOCK_MARK);


    QRegularExpressionMatch mainBlockMatch = RX_MAIN.match(source);
    if (mainBlockMatch.hasMatch() )
    {
        currBlock = mainBlockMatch.captured(0);
        cleanBlock(currBlock);

        result.append(currBlock);
    }

    source.replace(RX_MAIN, BLOCK_MARK);

    return result;

}   /* extractBlocks */


QStringList getSectionIds(QString section)
{
    QStringList result;

    QRegularExpressionMatchIterator varPartIter = RX_VAR_IDS.globalMatch(section);
    if (!varPartIter.hasNext() )
        return result;  // empty

    QString currPart;
    while (varPartIter.hasNext() )
    {
        currPart = varPartIter.next().captured(VAR_IDS_GROUP).remove(RX_WHITE_SPACES);

        if (!currPart.isEmpty() )
        {
            result.append(currPart.split(COMMA) );
        }
    }

    return result;

}   /* getSectionIds */


void countGlobalVars(QString &source, uint &practical, uint &available)
{
    practical = available = 0;

    QStringList blocks = extractBlocksEx(source);
    QRegularExpressionMatchIterator varSectionsIter = RX_VAR_SECTION.globalMatch(source);

    QString currSection;
    while (varSectionsIter.hasNext() )
    {
        QRegularExpressionMatch currMatch = varSectionsIter.next();
        currSection = currMatch.captured(VAR_SECTION_GROUP);

        if (!currSection.isEmpty() )
        {
            QStringList ids = getSectionIds(currSection);

            long long pos = currMatch.capturedStart(VAR_SECTION_GROUP);
            QRegularExpressionMatchIterator currModuleIter = RX_BLOCK_MARK.globalMatch(source, pos);

            uint count = 0;
            while(currModuleIter.hasNext() )
            {
                currModuleIter.next();
                ++count;
            }

            available += count * ids.count();

            foreach(QString b, blocks)
            {
                QRegularExpressionMatchIterator blockIter = makeListRegExp(ids).globalMatch(b);
                while (blockIter.hasNext() )
                {
                    ++practical;
                    blockIter.next();
                }
            }   // blocks
        }
    }   // var-sections

}   /* countGlobalVars */
