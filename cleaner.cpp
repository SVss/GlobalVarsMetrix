#include "stuff.h"
#include "regexes.h"

#include <QDebug>

void cleanSource(QString &source)
{
    source.remove(RX_STRING_LITERALS);

    source.remove(RX_SINGLELINE_COMMENTS);
    source.remove(RX_MULTILINE_COMMENTS);

    source.remove(RX_FORWARD_DECL);

}   /* cleanSource */

//=============================================================

QStringList getLocalDefs(QString block, ConstRegExp OUTER_REG, const uint outerCapGroup,
                         ConstRegExp INNER_REG, const uint innerCapGroup,
                         ConstRegExp REMOVE_REG = ConstRegExp() )
{
    QStringList result;
    QString params, currParam;

    QRegularExpressionMatchIterator currMatchIter = OUTER_REG.globalMatch(block);
    while (currMatchIter.hasNext() )
    {
        params = currMatchIter.next().captured(outerCapGroup);

        QRegularExpressionMatchIterator currPartIter = INNER_REG.globalMatch(params);
        while (currPartIter .hasNext() )
        {
            currParam = currPartIter .next().captured(innerCapGroup).remove(REMOVE_REG).remove(RX_WHITE_SPACES);

            if (!currParam.isEmpty() )
                result.append(currParam.split(",") );
        }
    }

    return result;

}   /* getLocalDefs */

//==================== VAR CONSTS =============================

void delLocalVarConsts(QString &block)
{
    QStringList localsDefsList;

    localsDefsList = getLocalDefs(block, RX_CAPTION, CAPTION_GROUP,
        RX_CAPTION_PARAMS, CAPTION_PARAMS_GROUP, RX_PARAM_OPERATORS);

    block.remove(RX_CAPTION);

    localsDefsList += getLocalDefs(block, RX_VAR_CONST_SECTION, VAR_CONST_SECTION_GROUP,
        RX_VAR_CONST_IDENTIFIERS, VAR_CONST_IDENTIFIERS_GROUP);

//    block.replace(RX_CAPTION, " ");
    block.replace(RX_VAR_CONST_SECTION, " ");

    if (!localsDefsList.isEmpty())
    {
        block.replace(makeListRegExp(localsDefsList), " ");
    }

}   /* delLocalVarConsts */

//==================== USER TYPES =============================

void delLocalUserTypes(QString &block)
{
    QStringList localTypesList = getLocalDefs(block, RX_TYPE_SECTION, TYPE_SECTION_GROUP, RX_LOCAL_TYPES, LOCAL_TYPES_GROUP);

    if (!localTypesList.isEmpty())
    {
        block.replace(makeListRegExp(localTypesList), " ");
    }

}   /* delLocalUserTypes */

//========================= ENUMS =============================

/*
QStringList getSectionEnums(QString &section)
{
    QStringList result;
    QRegularExpressionMatchIterator currMatchIter = RX_ENUMERATED.globalMatch(section);

    while (currMatchIter.hasNext() )
    {
        result.append(currMatchIter.next().captured(ENUMERATED_GROUP).remove(RX_WHITE_SPACES).split(",") );
    }

    return result;

}   // getSectionEnums */

/*

QStringList getEnumConsts(QString &block)
{
    QStringList result;
    QString currSection;

    QRegularExpressionMatchIterator currMatchIter = RX_VAR_TYPE_SECTION.globalMatch(block);

    while (currMatchIter.hasNext() )
    {
        currSection = currMatchIter.next().captured(0);
        result.append(getSectionEnums(currSection) );
    }

    return result;

}   // getEnumConsts */


void delLocalEnumConsts(QString &block)
{
    QStringList enumConstsDefs =
            getLocalDefs(block, RX_VAR_TYPE_SECTION, VAR_TYPE_SECTION_GROUP, RX_ENUMERATED, ENUMERATED_GROUP);

    if (!enumConstsDefs.isEmpty() )
    {
        block.replace(makeListRegExp(enumConstsDefs), " ");
    }

}   /* delLocalEnumConsts */

//============================================================

QString cleanBlock(QString &block)
{
    delLocalEnumConsts(block);

    delLocalUserTypes(block);

    delLocalVarConsts(block);

    return block;

} /* cleanBlock */
