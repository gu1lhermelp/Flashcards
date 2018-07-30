#include "main_window.h"
#include <iostream>
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include "tree_model.h"
#include <QTreeView>


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/flashcards");
    if (!db.open()) {
        QMessageBox::warning(0, "Log", QString("Database Error: %1").arg(db.lastError().text()));
        return 1;
    }

    QSqlQuery q;
    q.exec(
        "CREATE TABLE IF NOT EXISTS topic (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            name VARCHAR(40) UNIQUE NOT NULL);");
    q.exec(
        "CREATE TABLE subtopic (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            topic_id INTEGER NOT NULL,\
            name VARCHAR(80) NOT NULL,\
            UNIQUE (topic_id, name),\
            FOREIGN KEY(topic_id) REFERENCES topic(id));");
    q.exec(
        "CREATE TABLE flashcard (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            t_id INTEGER NOT NULL,\
            st_id INTEGER NOT NULL,\
            question VARCHAR(255) NOT NULL,\
            answer_type ENUM(0, 1) NOT NULL DEFAULT 0,\
            answer VARCHAR(255) NOT NULL,\
            FOREIGN KEY(t_id) REFERENCES topic(id),\
            FOREIGN KEY(st_id) REFERENCES subtopic(id));");

    MainWindow *w = new MainWindow(0);
    w->show();
    // QTreeView *tree = new QTreeView();
    // TreeModel *model = new TreeModel(tree);
    // connect(tree &QTreeView.expanded, this []
    // tree->setModel(model);
    // tree->show();
    app.setStyleSheet(
        "* {\
            font-size: 16pt;\
        }\
        #AddCard, #ViewCards {\
            font-size: 16pt;\
            padding: 20px 20px 20px 20px;\
            height: 100px;\
            width: 200px;\
            color: white;\
        }\
        QPushButton#AddCard {\
            background-color: blue;\
        }\
        QPushButton#ViewCards {\
            background-color: green;\
        }\
        QPushButton#Exit {\
            color: white;\
            background-color: red;\
        }\
        QLabel#Title {\
            font-size: 20pt;\
            font-weight: bold;\
        }\
        QLabel#Question { \
            font-size: 24px; \
            font-weight: bold; \
            background-color: #FFFFCC; \
            padding: 20px 20px 20px 20px; \
        }\
        QLabel#Topic {\
            font-size: 16px;\
            font-weight: bold;\
        }\
        QLabel#SubTopic {\
            font-size: 12px;\
            font-weight: bold;\
            color: gray;\
        }\
        QPushButton#AddTopic,\
        QPushButton#AddSubTopic {\
            color: white;\
            background-color: green;\
            font-weight: bold;\
            max-width: 30px;\
            max-height: 30px;\
        }\
        #RegisterFlashcardDlg QLabel {\
            font-weight: bold;\
        }\
        QPushButton#Register {\
            color: white;\
            background-color: blue;\
        }\
        QPushButton#AddTopicBtn,\
        QPushButton#RmvTopicBtn {\
            color: white;\
            background-color: green;\
            font-weight: bold;\
            max-width: 50px;\
            max-height: 30px;\
        }\
        QPushButton#NextBtn, QPushButton#PreviousBtn, QPushButton#OkBtn {\
            color: white;\
            background-color: blue;\
        }\
        QPushButton#CloseBtn {\
            color: white;\
            background-color: red;\
        }\
        "
    );
    return app.exec();
}
