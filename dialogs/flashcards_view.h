#ifndef FLASHCARDS_VIEW_H
#define FLASHCARDS_VIEW_H

#include <QDialog>
#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "flashcardwidget.h"


class FlashcardsView : public QDialog {

    public:
        FlashcardsView(QString, QWidget *);

    private:
        void setupUI();
        int currentRow;
        void fillFlashCard();
        void nextFlashcard();
        void prevFlashcard();
        QString query;
        FlashCardWidget *flashcard;
        QSqlQueryModel *model;
        QPushButton *prev;
        QPushButton *next;
};

#endif
