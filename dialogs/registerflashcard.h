#ifndef REGISTERFLASHCARD_H
#define REGISTERFLASHCARD_H

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QRadioButton>


class RegisterFlashcard : public QDialog {

    public:
        RegisterFlashcard(QWidget *);
        // RegisterFlashcard(QString, QString, QWidget *);

    private:
        const QString TOPIC_QUERY = "SELECT name, id FROM topic ORDER BY name";
        void setupUI();
        int getAnswerType();
        void setAnswerType(bool);
        void querySubTopics(int);
        void addTopic();
        void addSubTopic();
        int registerFlashcard();
        QComboBox *topic;
        QComboBox *sub_topic;
        QTextEdit *question;
        QRadioButton *general;
        QRadioButton *code;
        QTextEdit *answer;
};

#endif
