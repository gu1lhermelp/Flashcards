#ifndef REGISTERSUBTOPIC_H
#define REGISTERSUBTOPIC_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QRegExp>


class RegisterSubTopic : public QDialog {

    public:
        RegisterSubTopic(QWidget *);
        // RegisterSubTopic(QString, QWidget *);

    private:
        const QRegExp empty = QRegExp(QString("(|\\s+.*)"));
        void setupUI();
        void registerSubTopic();
        bool isStringEmpty(QString);

        QComboBox *topic;
        QLineEdit *sub_topic;
};

#endif
