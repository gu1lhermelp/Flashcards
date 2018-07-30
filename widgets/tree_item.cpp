#include "tree_item.h"


TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) {
    m_parentItem = parent;
    m_itemData = data;
    checked = Qt::Unchecked;
}


TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}


void TreeItem::appendChild(TreeItem *item) {
    m_childItems.append(item);
}


TreeItem *TreeItem::child(int row) {
    return m_childItems.value(row);
}


int TreeItem::childCount() const {
    return m_childItems.count();
}


int TreeItem::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}


int TreeItem::columnCount() const {
    return m_itemData.count();
}


QVariant TreeItem::data(int column) const {
    return m_itemData.value(column);
}


TreeItem *TreeItem::parentItem() {
    return m_parentItem;
}


Qt::CheckState TreeItem::getChecked() const {
    return checked;
}


void TreeItem::setChecked(Qt::CheckState set) {
    checked = set;
    for (TreeItem* child : m_childItems) {
        child->setChecked(set);
    }
    setParent(this);
}

void TreeItem::setParent(TreeItem *item) {
    TreeItem *parent = item->parentItem();
    if (parent != 0) {
        int child_count = parent->childCount();
        int checked = 0, unchecked = 0;
        for (int i = 0; i < child_count; i++) {
            if (parent->child(i)->getChecked() == Qt::Checked) {
                checked ++;
            } else {
                unchecked++;
            }
        }

        if (checked == child_count) {
            parent->check(Qt::Checked);
        } else if (unchecked == child_count) {
            parent->check(Qt::Unchecked);
        } else {
            parent->check(Qt::PartiallyChecked);
        }
    }
}

void TreeItem::check(Qt::CheckState set) {
    checked = set;
}
