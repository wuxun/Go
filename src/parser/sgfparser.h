#ifndef SGFPARSER_H
#define SGFPARSER_H

#include "gamerecord.h"
#include <QMap>

class QTextStream;
class QString;
class RecordNode;

class Move {
public:
    int x;
    int y;
};

class SgfParser
{
private:
    QMap<QString, PropType> convertTable;

    void initConvertTable();
    bool isMove(PropType type);
    PropType getPropType(QString &str);
    Move parseCoordinate(QString &str);
public:
    SgfParser();

    bool doParse(QTextStream &in, RecordNode *record);
    bool parseNodeStr(QString &nodeStr, RecordNode *node);
};

#endif // SGFPARSER_H
