#include "registerflashcard.h"
#include "registertopic.h"
#include "registersubtopic.h"
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QFont>
#include <QFontMetrics>
#include <iostream>


RegisterFlashcard::RegisterFlashcard(QWidget *parent = 0) : QDialog(parent) {
    setupUI();
    setObjectName("RegisterFlashcardDlg");
}


void RegisterFlashcard::setupUI() {
    QFormLayout *layout = new QFormLayout();
    QHBoxLayout *topic_layout = new QHBoxLayout();
    QHBoxLayout *sub_topic_layout = new QHBoxLayout();
    // QVBoxLayout *answer_layout = new QVBoxLayout();
    // QHBoxLayout *card_layout = new QHBoxLayout();
    QHBoxLayout *answer_type_layout = new QHBoxLayout();
    // Topic combo box
    topic = new QComboBox(this);
    QPushButton *addTopic = new QPushButton("+", this);
    addTopic->setObjectName("AddTopic");
    addTopic->setToolTip("Add new topic");
    topic_layout->addWidget(topic);
    topic_layout->addWidget(addTopic);
    QSqlQueryModel *topic_model = new QSqlQueryModel();
    topic_model->setQuery(TOPIC_QUERY);
    topic->setModel(topic_model);
    connect(
        topic,
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, &RegisterFlashcard::querySubTopics);
    connect(addTopic, &QPushButton::pressed,
            this, &RegisterFlashcard::addTopic);
    // Sub topic combo box
    sub_topic = new QComboBox(this);
    QPushButton *addSubTopic = new QPushButton("+", this);
    addSubTopic->setObjectName("AddSubTopic");
    sub_topic->setToolTip("Add new sub topic");
    sub_topic_layout->addWidget(sub_topic);
    sub_topic_layout->addWidget(addSubTopic);
    QSqlQueryModel *sub_topic_model = new QSqlQueryModel();
    sub_topic->setModel(sub_topic_model);
    querySubTopics(0);
    connect(addSubTopic, &QPushButton::pressed,
            this, &RegisterFlashcard::addSubTopic);
    // Question area
    question = new QTextEdit(this);
    // Question area
    answer = new QTextEdit(this);
    // Answer type
    general = new QRadioButton("General", this);
    code = new QRadioButton("Code", this);
    answer_type_layout->addWidget(general);
    answer_type_layout->addWidget(code);
    connect(general, &QRadioButton::toggled, this, &RegisterFlashcard::setAnswerType);
    general->setChecked(true);
    // answer_layout->addLayout(answer_type_layout);
    // answer_layout->addWidget(answer);
    // card_layout->addWidget(question);
    // card_layout->addLayout(answer_layout);
    // Button
    QPushButton *reg_flashcard = new QPushButton("Register", this);
    reg_flashcard->setObjectName("Register");
    QPushButton *close = new QPushButton("Close", this);
    close->setObjectName("CloseBtn");
    connect(close, &QPushButton::pressed,
            this, &RegisterFlashcard::reject);
    connect(reg_flashcard, &QPushButton::pressed,
            this, &RegisterFlashcard::registerFlashcard);
    // Set layout
    layout->addRow("Topic", topic_layout);
    layout->addRow("Sub Topic", sub_topic_layout);
    layout->addRow("Question", question);
    layout->addRow("Answer Type", answer_type_layout);
    layout->addRow("Answer", answer);
    layout->addRow(reg_flashcard);
    layout->addRow(close);
    layout->setLabelAlignment(Qt::AlignRight);
    setLayout(layout);
}


int RegisterFlashcard::getAnswerType() {
    return general->isChecked() ? 0 : 1;
}


void RegisterFlashcard::querySubTopics(int index) {
    int id = topic->model()->index(index, 1).data().toInt();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, id FROM subtopic WHERE topic_id == :id");
    query->bindValue(":id", id);
    query->exec();
    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(sub_topic->model());
    model->setQuery(*query);
    sub_topic->setCurrentIndex(0);
    delete query;
}


int RegisterFlashcard::registerFlashcard() {
    QSqlQuery *q;
    int t_id, st_id;
    int result = QMessageBox::question(0, QString("Register new flashcard"),
                                       QString("Register new flashcard?"));
    if (result == QMessageBox::Yes) {
        q = new QSqlQuery();
        t_id = topic->model()->index(topic->currentIndex(), 1).data().toInt();
        st_id = sub_topic->model()->index(
            sub_topic->currentIndex(), 1).data().toInt();
        q->prepare("INSERT INTO\
                    flashcard(t_id, st_id, question, answer_type, answer)\
                    VALUES(:t_id, :st_id, :question, :at, :answer)");
        q->bindValue(":t_id", t_id);
        q->bindValue(":st_id", st_id);
        q->bindValue(":question", question->toPlainText());
        q->bindValue(":at", getAnswerType());
        q->bindValue(":answer", answer->toPlainText());
        q->exec();
        if (q->lastError().isValid()) {
            // error
            QMessageBox::warning(0, QString("Error"),
                                 QString("Something went wrong!"));
        } else {
            // QMessageBox::information(0, QString("Flashcard saved"),
            //                          QString("New flashcard registered!"));
            // accept();
            question->clear();
            answer->clear();
            question->setFocus();
        }
        delete q;
    }
    return 0;
}


void RegisterFlashcard::setAnswerType(bool type) {
    QFont font;
    QFontMetrics metrics(font);
    if (type == true) {
        font.setFamily("Arial");
        font.setStyleHint(QFont::AnyStyle);
        font.setPointSize(14);

    } else {
        font.setFamily("Menlo");
        font.setStyleHint(QFont::TypeWriter);
        font.setFixedPitch(true);
        font.setPointSize(12);
    }
    answer->setFont(font);
    answer->setTabStopWidth(4 * metrics.width(' '));
}


void RegisterFlashcard::addTopic() {
    RegisterTopic *w = new RegisterTopic(this);
    w->exec();
    // if (result == 1) {
    QSqlQueryModel *m = dynamic_cast<QSqlQueryModel *>(topic->model());
    if (m != nullptr) {
        m->clear();
        m->setQuery(TOPIC_QUERY);
        topic->setCurrentIndex(0);
    }
    // }
    delete w;
}


void RegisterFlashcard::addSubTopic() {
    RegisterSubTopic *w = new RegisterSubTopic(this);
    w->exec();
    // if (result == 1) {
    querySubTopics(topic->currentIndex());
    // }
    delete w;
}
