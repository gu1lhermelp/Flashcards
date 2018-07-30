#ifndef SELECTION_H
#define SELECTION_H


#include <QWidget>
#include <QDialog>
#include <QStringList>
#include <QString>
#include <QTreeView>
#include "selection_widget.h"


class SelectionDialog : public QDialog {

public:
    SelectionDialog(QString, QWidget *);
    // QStringList getSelected();
    QTreeView *getTree();

private:
    void setupUI();
    QString query;
    // SetSelection *selection_widget;
    QTreeView *tree;
};

#endif
