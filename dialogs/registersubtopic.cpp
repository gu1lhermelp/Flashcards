#include "registersubtopic.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>


RegisterSubTopic::RegisterSubTopic(QWidget *parent = 0) : QDialog(parent) {
    setupUI();
}


// RegisterSubTopic::RegisterSubTopic(QString topic, QWidget *parent = 0) : QDialog(parent) {
//     setupUI();
// }


void RegisterSubTopic::setupUI() {
    QFormLayout *layout = new QFormLayout();
    topic = new QComboBox(this);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT name, id from topic ORDER BY name");
    topic->setModel(model);
    sub_topic = new QLineEdit(this);
    QPushButton *reg_subtopic = new QPushButton("Register", this);
    reg_subtopic->setObjectName("Register");
    QPushButton *close = new QPushButton("Close", this);
    close->setObjectName("CloseBtn");
    // Connect button to register method
    connect(reg_subtopic, &QPushButton::pressed, this, &RegisterSubTopic::registerSubTopic);
    connect(close, &QPushButton::pressed,
            this, &RegisterSubTopic::reject);
    layout->addRow(topic);
    layout->addRow(QString("Sub Topic Name:"), sub_topic);
    layout->addRow(reg_subtopic);
    layout->addRow(close);
    setLayout(layout);
}


void RegisterSubTopic::registerSubTopic() {
    int result;
    int id = topic->model()->index(topic->currentIndex(), 1).data().toInt();
    QString topic_name = topic->currentText();
    QString sub_topic_name = sub_topic->text();
    if (isStringEmpty(topic_name) || isStringEmpty(sub_topic_name)) {
        QMessageBox::information(0, "Empty Field", "Field value not allowed.");
        if (isStringEmpty(topic_name)) {
            // topic->clear();
            topic->setFocus();
        } else {
            sub_topic->clear();
            sub_topic->setFocus();
        }
    } else {
        result = QMessageBox::question(0, QString("Register sub topic"), QString("Register new sub topic %1 for topic %2?").arg(sub_topic_name, topic_name));
        if (result == QMessageBox::Yes) {
            QSqlQuery *q = new QSqlQuery();
            q->prepare("INSERT INTO subtopic(topic_id, name) VALUES(:id, :name)");
            q->bindValue(":id", id);
            q->bindValue(":name", sub_topic_name);
            q->exec();
            // accept();
            sub_topic->clear();
            sub_topic->setFocus();
        } else {
            sub_topic->setFocus();
        }
    }
}


bool RegisterSubTopic::isStringEmpty(QString str) {
    return empty.exactMatch(str);
}
