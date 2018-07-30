#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>
#include <QRegExp>
#include "registertopic.h"


RegisterTopic::RegisterTopic(QWidget *parent = 0) : QDialog(parent) {
    setupUI();
}

void RegisterTopic::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout();
    topic_edit = new QLineEdit(this);
    QLabel *topic = new QLabel("Topic Name:", this);
    topic->setBuddy(topic_edit);
    QPushButton *add_topic = new QPushButton(tr("Register"), this);
    add_topic->setObjectName("Register");
    QPushButton *close = new QPushButton("Close", this);
    close->setObjectName("CloseBtn");
    connect(add_topic, &QPushButton::pressed, this, &RegisterTopic::registerTopic);
    connect(close, &QPushButton::pressed, this, &RegisterTopic::reject);
    layout->addWidget(topic);
    layout->addWidget(topic_edit);
    layout->addWidget(add_topic);
    layout->addWidget(close);
    setLayout(layout);
}

void RegisterTopic::registerTopic() {
    int result;
    QRegExp empty(QString("(|\\s+.*)"));
    QString topic_name = topic_edit->text();
    if (empty.exactMatch(topic_name)) {
        QMessageBox::information(0, "Empty", "Name for topic not allowed.");
        topic_edit->clear();
        topic_edit->setFocus();
    } else {
        result = QMessageBox::question(0, QString("Register topic"), QString("Register new topic %1?").arg(topic_name));
        if (result == QMessageBox::Yes) {
            QSqlQuery *q = new QSqlQuery();
            q->prepare("INSERT INTO topic(name) VALUES(:name)");
            q->bindValue(":name", QVariant(topic_name));
            q->exec();
            accept();
        } else {
            reject();
        }
    }
}
