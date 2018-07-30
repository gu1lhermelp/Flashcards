#include "flashcardwidget.h"
#include <QVBoxLayout>
#include <Qt>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>

FlashCardWidget::FlashCardWidget(QWidget *parent = 0)
        : QWidget(parent){
    // this->flashcard = flashcard;
    setupUI();
}


void FlashCardWidget::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    t_l = new QLabel(this);
    t_l->setObjectName("Topic");
    st_l= new QLabel(this);
    st_l->setObjectName("SubTopic");
    q_l = new QLabel(this);
    q_l->setObjectName("Question");
    a_l = new QLabel(this);

    q_l->setWordWrap(true);
    q_l->setAlignment(Qt::AlignCenter);
    // a_l->setReadOnly(true);
    a_l->setAlignment(Qt::AlignCenter);

    t_w = new QTabWidget(this);
    t_w->setTabBarAutoHide(true);
    t_w->addTab(q_l, tr("Question"));
    t_w->addTab(a_l, tr("Answer"));

    layout->addWidget(t_l);
    layout->addWidget(st_l);
    layout->addWidget(t_w);

    setLayout(layout);
}


void FlashCardWidget::setAnswerType(int answer_type) {
    if (answer_type == 0) {
        a_l->setAlignment(Qt::AlignCenter);
        a_l->setStyleSheet(
            "font: 14pt Arial;\
             background-color: #FFFFCC; \
             padding: 20px 20px 20px 20px;"

        );
    } else {
        a_l->setAlignment(Qt::AlignLeft);
        a_l->setStyleSheet(
                "font: 12pt Menlo, Consolas, DejaVu Sans Mono, monospace;\
                 background-color: #FFFFCC; \
                 padding: 20px 20px 20px 20px;"
        );
    }
}


QLabel* FlashCardWidget::getTopicLabel() {
    return t_l;
}


QLabel* FlashCardWidget::getSubTopicLabel() {
    return st_l;
}


QLabel* FlashCardWidget::getQuestionLabel() {
    return q_l;
}


QLabel* FlashCardWidget::getAnswerLabel() {
    return a_l;
}


QTabWidget* FlashCardWidget::getTabWidget() {
    return t_w;
}
