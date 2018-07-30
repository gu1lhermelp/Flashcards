#include "flashcards_view.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QDataWidgetMapper>
#include <QFont>


FlashcardsView::FlashcardsView(QString query, QWidget *parent = 0) : QDialog(parent) {
    this->query = query;
    currentRow = 0;
    setupUI();
    fillFlashCard();
}


void FlashcardsView::setupUI() {
    /* Setup dialog UI.*/
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *btn_layout = new QHBoxLayout();
    // Flashcard is the main widget use to view flashcard data
    flashcard = new FlashCardWidget(this);
    prev = new QPushButton("Prev", this);
    next = new QPushButton("Next", this);
    QPushButton * close = new QPushButton("Close", this);
    btn_layout->addWidget(prev);
    btn_layout->addWidget(next);
    btn_layout->addWidget(close);
    connect(prev, &QPushButton::pressed, this, &FlashcardsView::prevFlashcard);
    connect(next, &QPushButton::pressed, this, &FlashcardsView::nextFlashcard);
    connect(close, &QPushButton::pressed, this, &FlashcardsView::reject);
    // Set model
    model = new QSqlQueryModel(this);
    model->setQuery(query);
    // Add widgets
    layout->addWidget(flashcard);
    layout->addLayout(btn_layout);

    setLayout(layout);

    prev->setObjectName("PreviousBtn");
    next->setObjectName("NextBtn");
    close->setObjectName("CloseBtn");
}


void FlashcardsView::fillFlashCard() {
    int answer_type;
    QString topic, sub_topic, question, answer;

    topic = model->index(currentRow, 0).data().toString();
    sub_topic = model->index(currentRow, 1).data().toString();
    question = model->index(currentRow, 2).data().toString();
    answer_type = model->index(currentRow, 3).data().toInt();
    answer = model->index(currentRow, 4).data().toString();

    flashcard->getTopicLabel()->setText(topic);
    flashcard->getSubTopicLabel()->setText(sub_topic);
    flashcard->getQuestionLabel()->setText(question);
    flashcard->setAnswerType(answer_type);
    flashcard->getAnswerLabel()->setText(answer);
}


void FlashcardsView::prevFlashcard() {
    flashcard->getTabWidget()->setCurrentIndex(0);
    next->setEnabled(true);
    currentRow -= 1;
    if (currentRow < 0) {
        currentRow += 1;
        prev->setEnabled(false);
    } else if (currentRow == 0) {
        prev->setEnabled(false);
    } else {
        prev->setEnabled(true);
    }
    fillFlashCard();
}


void FlashcardsView::nextFlashcard() {
    flashcard->getTabWidget()->setCurrentIndex(0);
    prev->setEnabled(true);
    currentRow += 1;
    if (currentRow > model->rowCount() - 1) {
        currentRow -= 1;
        next->setEnabled(false);
    } else if (currentRow == model->rowCount() - 1) {
        next->setEnabled(false);
    } else {
        next->setEnabled(true);
    }
    fillFlashCard();
}
