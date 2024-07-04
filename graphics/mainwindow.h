#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawarea.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setLineShape();
    void setRectangleShape();
    void setCircleShape();
    void setPenColor();
    void setFillColor();
    void saveAsText();
    void loadFromText();

private:
    DrawArea *drawArea;
};

#endif // MAINWINDOW_H
