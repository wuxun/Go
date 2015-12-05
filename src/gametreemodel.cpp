#include "gametreemodel.h"

#include <QIcon>

GameTreeModel::GameTreeModel(QObject *parent):QAbstractItemModel(parent)
{
    root = NULL;
}

GameTreeModel::~GameTreeModel()
{
    if (root != NULL) {
        // free root and childrens
    }
}

QVariant GameTreeModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    RecordNode *item = static_cast<RecordNode*>(index.internalPointer());

    if(role==Qt::DisplayRole)
    {
        return QVariant(item->getCoordinate());
    }

    if(role==Qt::DecorationRole&&index.column()==0) {
        if (item->moveType == PropType::BLACK_MOVE) {
            return QIcon(":resources/stone_black_small.png");
        } else if (item->moveType == PropType::WHITE_MOVE) {
            return QIcon(":resources/stone_white_small.png");
        }
    }

    return QVariant();
}

QModelIndex GameTreeModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row,column,parent))
        return QModelIndex();

    RecordNode *parentItem;
    if (!parent.isValid()) {
        parentItem = root;
    } else {
        parentItem = static_cast<RecordNode*>(parent.internalPointer());
    }

    RecordNode *childItem = parentItem->childrens.at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex GameTreeModel::parent(const QModelIndex & index) const
{
    if(!index.isValid())
        return QModelIndex();

    RecordNode *childItem = static_cast<RecordNode*>(index.internalPointer());
    RecordNode *parentItem = childItem->getParent();

    if(parentItem == root)
        return QModelIndex();

    // 为父结点建立索引
    return createIndex(parentItem->row(), 0, parentItem);
}

int GameTreeModel::rowCount(const QModelIndex & parent) const
{
    RecordNode *parentItem;

    if(!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<RecordNode*>(parent.internalPointer());

    return parentItem->childCount();
}

int GameTreeModel::columnCount(const QModelIndex & parent) const
{
    return 1;
}

void GameTreeModel::setModelData(RecordNode* node)
{
    root = new RecordNode;
    node->setParent(root);
    root->childrens.push_back(node);
}

