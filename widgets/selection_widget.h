#ifndef SET_SELECTION_H
#define SET_SELECTION_H


#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QSet>
#include <QString>


class SetSelection : public QWidget {

public:
    SetSelection(QString, QWidget *);
    QStringList getSelected();

private:
    void setupUI();
    void addToSelected();
    void rmvFromSelected();
    QString query;
    QSet<QString> selected;
    QListView source_view;
    QListWidget selected_view;
};


#endif
