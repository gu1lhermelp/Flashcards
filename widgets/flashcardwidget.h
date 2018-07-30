#ifndef FLASHCARDWIDGET_H
#define FLASHCARDWIDGET_H

#include <QLabel>
#include <QTabWidget>
#include <QSqlTableModel>

class FlashCardWidget : public QWidget {

    public:
        FlashCardWidget(QWidget *);
        QLabel* getTopicLabel();
        QLabel* getSubTopicLabel();
        QLabel* getQuestionLabel();
        QLabel* getAnswerLabel();
        QTabWidget * getTabWidget();
        void setAnswerType(int);
        void reset();

    private:
        void setupUI();
        QLabel *t_l;
        QLabel *st_l;
        QLabel *q_l;
        QLabel *a_l;
        QTabWidget *t_w;
        QSqlTableModel *model;
};

#endif
