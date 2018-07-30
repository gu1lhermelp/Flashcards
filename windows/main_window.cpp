#include "registerflashcard.h"
#include "flashcards_view.h"
#include "selection_dialog.h"
#include "main_window.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <iostream>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include "tree_item.h"

MainWindow::MainWindow(QWidget *parent = 0) : QMainWindow(parent) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    w_height = screenGeometry.height();
    w_width = screenGeometry.width();
    setupUI();
    setWindowTitle("Flashcards Application");
    move((w_width - width())/2, (w_height - height())/2);
}


void MainWindow::setupUI() {
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *actions = new QHBoxLayout();
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    QPushButton *addCard = new QPushButton("Add Card", this);
    addCard->setObjectName("AddCard");
    QPushButton *viewCards = new QPushButton("View Cards", this);
    viewCards->setObjectName("ViewCards");
    QPushButton *ex = new QPushButton("Exit", this);
    ex->setObjectName("Exit");

    actions->addWidget(addCard);
    actions->addWidget(viewCards);

    layout->addLayout(actions);
    layout->addWidget(ex);

    connect(addCard, &QPushButton::pressed, this, &MainWindow::addCard);
    connect(viewCards, &QPushButton::pressed, this, &MainWindow::viewCards);
    connect(ex, &QPushButton::pressed, this, &MainWindow::close);
}


void MainWindow::addCard() {
    RegisterFlashcard *w = new RegisterFlashcard(this);
    w->exec();
    delete w;
}


void MainWindow::viewCards() {
    // TODO: add title to dialogsls
    QString query, title, fc_query;
    SelectionDialog *w;
    int dlg_width = 800;
    int dlg_height = 600;
    FlashcardsView *v;
    QStringList topics, sub_topics;
    fc_query =
        "SELECT t.name, st.name, question, answer_type, answer\
        FROM flashcard as fc\
        JOIN topic as t ON t_id=t.id\
        JOIN subtopic as st ON st_id=st.id\
        WHERE ";
    query = "SELECT name FROM topic ORDER BY name";
    w = new SelectionDialog(query, this);
    w->setGeometry((w_width - dlg_width)/2, (w_height - dlg_height)/2, dlg_width, dlg_height);
    int result = w->exec();
    if (result == 1) {
         QTreeView *tree = w->getTree();
         int row_count = tree->model()->rowCount();
         std::cout << row_count << std::endl;
         bool insert_or = false;
         for (auto i = 0; i < row_count; i++) {
             // Iterate topics
             Qt::CheckState s = static_cast<Qt::CheckState>(
                    tree->model()->index(i, 0).data(Qt::CheckStateRole).toInt());
            if (s == Qt::Unchecked) {
                continue;
            } else if (s == Qt::Checked) {
                // Get topic

                if (insert_or)
                    fc_query += "OR ";


                QString topic = tree->model()->index(i, 0).data().toString();
                fc_query += "t.name='" + topic + "' ";
                insert_or = true;
             } else {

                if (insert_or)
                    fc_query += "OR ";

                QModelIndex parent = tree->model()->index(i, 0);
                int child_count = tree->model()->rowCount(parent);
                QString topic = parent.data().toString();
                fc_query += "(t.name='" + topic + "' AND st.name IN('";
                QList<QString> st_list;
                for (auto j = 0; j < child_count; j++) {
                    QModelIndex item = tree->model()->index(j, 0, parent);
                    Qt::CheckState s = static_cast<Qt::CheckState>(
                            item.data(Qt::CheckStateRole).toInt());
                    if (s == Qt::Checked) {
                        st_list << item.data().toString();
                    }
                }
                fc_query += st_list.join("', '");
                fc_query += "')) ";
                insert_or = true;
            }
         }
    } else {
        return;
    }
    delete w;

    std::cout << fc_query.toStdString() << std::endl;



    // Build query to get subtopics
    // int count = topics.count();
    // int i = 1;
    // for (auto topic : topics) {
    //     query = QString(
    //         "SELECT subtopic.name\
    //         FROM topic JOIN subtopic ON topic.id=topic_id\
    //         WHERE topic.name='%1' ORDER BY subtopic.name").arg(topic);
    //     w = new SelectionDialog(query, this);
    //     w->setGeometry((w_width - dlg_width)/2, (w_height - dlg_height)/2, dlg_width, dlg_height);
    //     result = w->exec();
    //     if (result == 1) {
    //          sub_topics = w->getSelected();
    //     } else {
    //         return;
    //     }
    //     fc_query += "(t.name='" + topic + "' AND st.name IN ('";
    //     fc_query += sub_topics.join("', '");
    //     fc_query += "'))";
    //     if (i != count) {
    //         fc_query += " OR ";
    //     }
    //     delete w;
    //     i++;
    // }

    v = new FlashcardsView(fc_query, this);
    dlg_width = 1024;
    dlg_height = 600;
    v->setGeometry((w_width - dlg_width)/2, (w_height - dlg_height)/2, dlg_width, dlg_height);
    v->exec();
    delete v;
}
