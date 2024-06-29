#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveToFile();
    void loadFromFile();
    void addNewRow();
    void saveToExcel();
    void loadFromExcel();

private:
    QTableView *tableView;
    QStandardItemModel *model;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionSaveExcel;
    QAction *actionLoadExcel;
    QPushButton *addRowButton;
};

#endif // MAINWINDOW_H
