#include "regexes.h"

ConstRegExp makeListRegExp(QStringList list)
{
    QString regex_text = "\\b(" + list.join("|") + ")\\b";
    return QRegularExpression(regex_text);
}
