#include "sgfparser.h"
#include "gamerecord.h"
#include <QTextStream>
#include <QDebug>
#include <QStack>

SgfParser::SgfParser()
{
    initConvertTable();
}

void SgfParser::initConvertTable()
{
    //Move properties
    convertTable.insert("B", PropType::BLACK_MOVE);
    convertTable.insert("KO", PropType::KO);
    convertTable.insert("MN", PropType::MOVE_NUMBER);
    convertTable.insert("W", PropType::WHITE_MOVE);

    //Setup properties
    convertTable.insert("AB", PropType::ADD_BLACK);
    convertTable.insert("AE", PropType::ADD_ERASE);
    convertTable.insert("AW", PropType::ADD_WHITE);
    convertTable.insert("PL", PropType::PLAYER_TURN);

    //Node annotation properties
    convertTable.insert("C", PropType::COMMENT);
    convertTable.insert("DM", PropType::EVEN_POSITION);
    convertTable.insert("GB", PropType::GOOD_FOR_BLACK);
    convertTable.insert("GW", PropType::GOOD_FOR_WHITE);
    convertTable.insert("HO", PropType::HOTSPOT);
    convertTable.insert("N", PropType::NODE_NAME);
    convertTable.insert("UC", PropType::UNCLEAR_POS);
    convertTable.insert("V", PropType::NODE_VALUE);

    //Move annotation properties
    convertTable.insert("BM", PropType::BAD_MOVE);
    convertTable.insert("DO", PropType::DOUBTFUL_MOVE);
    convertTable.insert("IT", PropType::INTERESTING_MOVE);
    convertTable.insert("TE", PropType::TESUJI_MOVE);

    //Markup properties
    convertTable.insert("AR", PropType::ARROW_MARK);
    convertTable.insert("CR", PropType::CIRCLE_MARK);
    convertTable.insert("DD", PropType::DIM_POINT);
    convertTable.insert("LB", PropType::TEXT_MARK);
    convertTable.insert("LN", PropType::LINE_MARK);
    convertTable.insert("MA", PropType::X_MARK);
    convertTable.insert("SL", PropType::SELECTED_POINT);
    convertTable.insert("SQ", PropType::SQUARE_MARK);
    convertTable.insert("TR", PropType::TRIANGLE_MARK);

    //Root properties
    convertTable.insert("AP", PropType::APPLICATION);
    convertTable.insert("CA", PropType::CHARSET);
    convertTable.insert("FF", PropType::FILE_FORMAT);
    convertTable.insert("GM", PropType::GAME_TYPE);
    convertTable.insert("ST", PropType::VARIATIONS_SHOW);
    convertTable.insert("SZ", PropType::SIZE);

    //Game info properties
    convertTable.insert("AN", PropType::ANNOTATION_PERSON_NAME);
    convertTable.insert("BR", PropType::BLACK_RANK);
    convertTable.insert("BT", PropType::BLACK_TEAM);
    convertTable.insert("CP", PropType::COPYRIGHT);
    convertTable.insert("DT", PropType::PLAYED_DATE);
    convertTable.insert("EV", PropType::EVENT_NAME);
    convertTable.insert("GN", PropType::GAME_NAME);
    convertTable.insert("GC", PropType::EXTRA_INFO);
    convertTable.insert("ON", PropType::OPENING_INFO);
    convertTable.insert("OT", PropType::OVERTIME_METHOD);
    convertTable.insert("PB", PropType::BLACK_PLAYER);
    convertTable.insert("PC", PropType::PLACE);
    convertTable.insert("PW", PropType::WHITE_PLAYER);
    convertTable.insert("RE", PropType::RESULT);
    convertTable.insert("RO", PropType::ROUND);
    convertTable.insert("RU", PropType::RULES);
    convertTable.insert("SO", PropType::SOURCE);
    convertTable.insert("TM", PropType::TIME_LIMIT);
    convertTable.insert("US", PropType::USER_NAME);
    convertTable.insert("WR", PropType::WHITE_RANK);
    convertTable.insert("WT", PropType::WHITE_TEAM);

    //Timing properties
    convertTable.insert("BL", PropType::BLACK_TIME_LEFT);
    convertTable.insert("OB", PropType::BLACK_MOVE_LEFT);
    convertTable.insert("OW", PropType::WHITE_MOVE_LEFT);
    convertTable.insert("WL", PropType::WHITE_TIME_LEFT);

    //Miscellaneous properties
    convertTable.insert("FG", PropType::FIGURE_PROP);
    convertTable.insert("PM", PropType::PRINTING_METHOD);
    convertTable.insert("VW", PropType::VIEW_PART);

    //GO specific properties
    convertTable.insert("HA", PropType::HANDICAP);
    convertTable.insert("KM", PropType::KOMI);
    convertTable.insert("TB", PropType::BLACK_TERRITORY);
    convertTable.insert("TW", PropType::WHITE_TERRITORY);
}

PropType SgfParser::getPropType(QString &str)
{
    QMap<QString, PropType>::iterator ite = convertTable.find(str);
    if (ite != convertTable.end()) {
        return ite.value();
    }
    return PropType::UNKNOWN;
}

bool SgfParser::isMove(PropType type)
{
    return type == PropType::BLACK_MOVE
            || type == PropType::WHITE_MOVE;
}

Move SgfParser::parseCoordinate(QString &str)
{
    Move move;
    move.x = str[0].toLatin1() - 'a';
    move.y = str[1].toLatin1() - 'a';
    return move;
}

bool SgfParser::doParse(QTextStream &in, RecordNode *root)
{
    QChar ch;
    in.setCodec("gb2312");

    QChar branchStart('(');
    QChar branchEnd(')');
    QChar nodeStart(';');

    RecordNode *current = NULL;
    QStack<RecordNode *> parents;
    bool startParse = true;
    bool hasPushBackChar = false;
    QChar pushBackChar;

    while (!in.atEnd()) {
        if (hasPushBackChar) {
            ch = pushBackChar;
            hasPushBackChar = false;
        } else {
            in >> ch;
        }

        if (ch == branchStart) {
            if (startParse == true) {
                startParse = false;
                parents.push(root);
            } else {
                RecordNode *tmpRecord = new RecordNode(parents.top());
                parents.top()->childrens.push_back(tmpRecord);
                parents.push(tmpRecord);
            }
            current = parents.top();
        } else if (ch == branchEnd) {
            parents.pop();
        } else if (ch == nodeStart) {
            QString nodeStr;
            QStack<QChar> pairNodeValue;
            in >> ch;
            while (!in.atEnd()) {
                if (ch == nodeStart && pairNodeValue.empty()) {
                    pushBackChar = nodeStart;
                    hasPushBackChar = true;
                    break;
                } else if (ch == branchStart && pairNodeValue.empty()) {
                    pushBackChar = branchStart;
                    hasPushBackChar = true;
                    break;
                } else if (ch == branchEnd && pairNodeValue.empty()) {
                    pushBackChar = branchEnd;
                    hasPushBackChar = true;
                    break;
                } else if (ch == '\\') {
                    in >> ch;
                    nodeStr += '\\' + ch;
                } else if (ch == '[' && pairNodeValue.empty()) {
                    pairNodeValue.push(nodeStart);
                    nodeStr += ch;
                } else if (ch == ']') {
                    if (pairNodeValue.empty()) {
                        qDebug() << "error format";
                        return false;
                    }
                    pairNodeValue.pop();
                    nodeStr += ch;
                } else {
                    nodeStr += ch;
                }
                in >> ch;
            }

            if (!nodeStr.isEmpty()) {
                if (current == NULL) {
                    current = new RecordNode(parents.top());
                    parents.top()->childrens.push_back(current);
                }

                if (!parseNodeStr(nodeStr, current)) {
                    qDebug() << "parse node error:" << nodeStr;
                    return false;
                }
                current = NULL;
            }
        } else if (ch.isSpace()) {
            // ignore white space
        } else {
            qDebug() << "Unknown char in sgf parse: " << ch;
            return false;
        }
    }
    return true;
}

bool SgfParser::parseNodeStr(QString &nodeStr, RecordNode *node)
{
    QChar valueStart('[');
    QChar valueEnd(']');

    int pos = 0;

    PropType type = PropType::UNKNOWN;
    QList<QString> *values = new QList<QString>;

    while (pos < nodeStr.size()) {
        if (nodeStr[pos].isLetter()) {
            QString key;
            while (nodeStr[pos].isLetter() && pos < nodeStr.size()) {
                key += nodeStr[pos];
                pos++;
            }

            type = getPropType(key);
            qDebug("key: %s ", key.toStdString().c_str());
            pos--;
        } else if (nodeStr[pos] == valueStart) {
            pos++;
            QString value;
            while (nodeStr[pos] != valueEnd && pos < nodeStr.size()) {
                if (nodeStr[pos] == '\\') {
                    pos++;
                    value += nodeStr[pos];
                } else {
                    value += nodeStr[pos];
                }
                pos++;
            }

            if (isMove(type)) {
                node->moveType = type;
                Move move = parseCoordinate(value);
                node->pos_x = move.x;
                node->pos_y = move.y;
            } else {
                values->append(value);
            }
            qDebug("value: %s", value.toStdString().c_str());
            pos--;
        } else if (nodeStr[pos] == valueEnd) {
            if (!isMove(type)) {
                while (nodeStr[++pos].isSpace() && pos < nodeStr.size()) {}
                if (pos == nodeStr.size()
                        || (pos < nodeStr.size() && nodeStr[pos] != valueStart)) {
                    node->extraProps.insert(type, values);
                    type = PropType::UNKNOWN;
                    values = new QList<QString>;
                }
                pos--;
            }
        } else {
            qDebug() << "unknown:" << nodeStr[pos];
        }
        pos++;
    }

    delete values;
    return true;
}
