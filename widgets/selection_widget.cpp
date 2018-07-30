#include "selection_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QModelIndex>


SetSelection::SetSelection(QString query, QWidget *parent = nullptr) : QWidget(parent) {
    this->query = query;
    setupUI();
}


void SetSelection::setupUI() {
    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *control = new QVBoxLayout();

    // source_view = new QListView(this);
    // selected_view = new QListView(this);

    QPushButton *add = new QPushButton(">>", this);
    add->setObjectName("AddTopicBtn");
    QPushButton *rmv = new QPushButton("<<", this);
    rmv->setObjectName("RmvTopicBtn");

    control->addWidget(add);
    control->addWidget(rmv);

    layout->addWidget(&source_view);
    layout->addLayout(control);
    layout->addWidget(&selected_view);

    setLayout(layout);

    // Connect buttons
    connect(add, &QPushButton::pressed, this, &SetSelection::addToSelected);
    connect(rmv, &QPushButton::pressed, this, &SetSelection::rmvFromSelected);

    // Set view models
    QSqlQueryModel *source_model = new QSqlQueryModel(this);
    source_model->setQuery(query);
    source_view.setModel(source_model);
    source_view.setSelectionMode(QListView::ExtendedSelection);
    selected_view.setSelectionMode(QListView::ExtendedSelection);
}


void SetSelection::addToSelected() {
    // selected.clear();
    for (QModelIndex index : source_view.selectionModel()->selectedIndexes()) {
        QString data = source_view.model()->index(index.row(), index.column()).data().toString();
        selected.insert(data);
    }
    selected_view.clear();
    selected_view.addItems(selected.toList());
}


void SetSelection::rmvFromSelected() {
    for (QModelIndex index : selected_view.selectionModel()->selectedIndexes()) {
        QString data = selected_view.model()->index(index.row(), index.column()).data().toString();
        selected.remove(data);
    }
    selected_view.clear();
    selected_view.addItems(selected.toList());
}


QStringList SetSelection::getSelected() {
    return QStringList(selected.toList());
}
