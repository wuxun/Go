#ifndef GAMETREEMODEL_H
#define GAMETREEMODEL_H

#include <QAbstractItemModel>
#include "parser/gamerecord.h"

class GameTreeModel : public QAbstractItemModel
{
public:
    GameTreeModel(QObject *parent = NULL);
    ~GameTreeModel();

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    void setModelData(RecordNode* node);

private:
    RecordNode *root;
};

#endif // GAMETREEMODEL_H
