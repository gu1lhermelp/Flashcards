#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "selection_dialog.h"
#include "tree_model.h"


SelectionDialog::SelectionDialog(QString query, QWidget *parent = nullptr) : QDialog(parent) {
    this->query = query;
    setupUI();
}


void SelectionDialog::setupUI() {
    // QVBoxLayout layout;
    // QHBoxLayout button_group;
    // QLabel title("Which topics would you like to memorize?", this);
    // QPushButton ok("Ok", this), cancel("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *button_group = new QHBoxLayout();

    QLabel *title = new QLabel("Which topics would you like to memorize?", this);
    // selection_widget = new SetSelection(query, this);
    tree = new QTreeView(this);
    TreeModel *model = new TreeModel(tree);
    tree->setModel(model);
    QPushButton *ok = new QPushButton("Ok", this);
    QPushButton *cancel = new QPushButton("Cancel", this);

    button_group->addWidget(ok);
    button_group->addWidget(cancel);

    layout->addWidget(title);
    layout->addWidget(tree);
    layout->addLayout(button_group);

    setLayout(layout);

    // Connect buttons
    connect(ok, &QPushButton::pressed, this, &SelectionDialog::accept);
    connect(cancel, &QPushButton::pressed, this, &SelectionDialog::reject);

    tree->setHeaderHidden(true);
    title->setObjectName("Title");
    ok->setObjectName("OkBtn");
    cancel->setObjectName("CloseBtn");
}


// QStringList SelectionDialog::getSelected() {
//     return selection_widget->getSelected();
// }

QTreeView* SelectionDialog::getTree() {
    return tree;
}
