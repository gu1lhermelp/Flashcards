#ifndef REGISTERTOPIC_H
#define REGISTERTOPIC_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>

class RegisterTopic : public QDialog {

    public:
        RegisterTopic(QWidget *);

    private:
        void setupUI();
        void registerTopic();

        QLineEdit *topic_edit;
};

#endif
