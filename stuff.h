#ifndef STUFF_H_
#define STUFF_H_

#include <QString>

extern const QString BLOCK_MARK;

void cleanSource(QString &source);
QString cleanBlock(QString &block);

void countGlobalVars(QString &source, uint &practical, uint &available);

#endif // STUFF_H_

