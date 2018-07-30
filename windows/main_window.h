#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QWidget>
#include <QMainWindow>


class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *);
private:
    void setupUI();
    void addCard();
    void viewCards();
    QMainWindow *window;
    int w_height, w_width;
};


#endif
