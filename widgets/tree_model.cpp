#include "tree_model.h"
#include <QSqlQuery>
#include <iostream>

TreeModel::TreeModel(QObject *parent)
        : QAbstractItemModel(parent) {
    QList<QVariant> rootData;
    rootData << "Name";
    rootItem = new TreeItem(rootData);
    setupModelData(rootItem);
}


TreeModel::~TreeModel() {
    delete rootItem;
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
    const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}


int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
        return item->getChecked();

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 0)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
    // return QAbstractItemModel::flags(index);
}



QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
    int role)
{
    if (index.column() == 0) {
        if (role == Qt::EditRole)
            return false;
        if (role == Qt::CheckStateRole) {
            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
            item->setChecked(static_cast<Qt::CheckState>(value.toInt()));

            QModelIndex top = createIndex(0, 0, item);
            QModelIndex bottom = createIndex(item->childCount() - 1, 0, item);

            dataChanged(index, index);
            dataChanged(top, bottom);
            return true;
        }
    }
    return false;
}

void TreeModel::setupModelData(TreeItem *parent)
{
    QList<TreeItem*> toplevel;
    QSqlQuery query("SELECT name, id FROM topic");

    while (query.next()) {
        QSqlQuery st_query;
        int topic_id = query.value(1).toInt();
        QString topic = query.value(0).toString();
        QList<QVariant> values;
        values << QVariant(topic) << QVariant(topic_id);

        toplevel << new TreeItem(values, parent);

        st_query.prepare(
                "SELECT name, id\
                 FROM subtopic WHERE topic_id=:topic_id");
        st_query.bindValue(":topic_id", topic_id);
        st_query.exec();
        // std::cout << st_query.executedQuery().toStdString() << std::endl;

        while (st_query.next()) {
            // std::cout << "Adding" << std::endl;
            QList<QVariant> values;
            values << st_query.value(0) << st_query.value(1);
            TreeItem *p = toplevel.last();
            p->appendChild(new TreeItem(values, p));
        }

        parent->appendChild(toplevel.last());
    }
}
