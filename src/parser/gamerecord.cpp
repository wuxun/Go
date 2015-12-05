#include "gamerecord.h"

RecordNode::RecordNode(RecordNode *node)
{
    pos_x = -1;
    pos_y = -1;
    moveType = PropType::UNKNOWN;
    parent = node;
}

void RecordNode::setParent(RecordNode *parent)
{
    this->parent = parent;
}

QString RecordNode::toString() {
    return nodeToStr(this);
}

int RecordNode::childCount()
{
    return childrens.size();
}

RecordNode* RecordNode::getParent()
{
    return parent;
}

int RecordNode::row()
{
    if (parent) {
        return parent->childrens.indexOf(this);
    }
    return 0;
}

QString RecordNode::getCoordinate()
{
    if (moveType != PropType::UNKNOWN) {
        char col;
        col = 'A' + pos_x;
        if (col > 'H') {
            col = col + 1;
        }

        QString row;
        row.setNum(19 - pos_y);
        return QChar(col) + row;
    }
    return QString();
}

QString RecordNode::nodeToStr(RecordNode *node) {
    QString str("");
    if (node->moveType == PropType::BLACK_MOVE) {
        str += "B:";
        str +=(new QString)->setNum(node->pos_x);
        str +=(new QString)->setNum(node->pos_y);
//            str += " ";
    } else if (node->moveType == PropType::WHITE_MOVE) {
        str += "W:" + (new QString)->setNum(node->pos_x) + (new QString)->setNum(node->pos_y);
//            str += " ";
    }

    if (!extraProps.isEmpty()) {
        QMapIterator<PropType, QList<QString> *> i(node->extraProps);
        while (i.hasNext()) {
            i.next();
            str += "prop: ";
            if (!i.value()->isEmpty()){
                str += i.value()->first();
            }
            str += " ";
        }
    }

    if (!childrens.isEmpty()) {
    QListIterator<RecordNode *> ite(node->childrens);
        while (ite.hasNext()) {
            RecordNode *tmp = ite.next();
            if (tmp == node->childrens.first()) {
                str += nodeToStr(tmp);
            } else {
                str += "(" + nodeToStr(tmp) + ")";
            }
        }
    }
    return str;
}
