#ifndef TREE_ITEM_H
#define TREE_ITEM_H


#include <QList>
#include <QVariant>


class TreeItem {
public:
    explicit TreeItem(const QList<QVariant>&data, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild(TreeItem *);

    TreeItem *child(int);
    int childCount() const;
    int columnCount() const;
    QVariant data(int) const;
    int row() const;
    TreeItem *parentItem();

    void setChecked(Qt::CheckState set);
    Qt::CheckState getChecked() const;
private:
    Qt::CheckState checked;
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
    void setParent(TreeItem *parent);
    void check(Qt::CheckState set);
};


#endif
