#include "mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем модель
    model = new QStandardItemModel(0, 3, this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Column 1"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Column 2"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Column 3"));

    // Создаем вид таблицы и задаем ему модель
    tableView = new QTableView(this);
    tableView->setModel(model);

    // Создаем кнопку для добавления новой строки
    addRowButton = new QPushButton(tr("Add Row"), this);
    connect(addRowButton, &QPushButton::clicked, this, &MainWindow::addNewRow);

    // Создаем компоновку
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableView);
    layout->addWidget(addRowButton);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Создаем действия
    actionSave = new QAction(tr("Save"), this);
    actionLoad = new QAction(tr("Load"), this);
    actionSaveExcel = new QAction(tr("Save as Excel"), this);
    actionLoadExcel = new QAction(tr("Load Excel"), this);

    // Подключаем действия к слотам
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveToFile);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::loadFromFile);
    connect(actionSaveExcel, &QAction::triggered, this, &MainWindow::saveToExcel);
    connect(actionLoadExcel, &QAction::triggered, this, &MainWindow::loadFromExcel);

    // Создаем меню и добавляем в него действия
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionLoad);
    fileMenu->addAction(actionSaveExcel);
    fileMenu->addAction(actionLoadExcel);
}

MainWindow::~MainWindow()
{
    delete model;
    delete tableView;
    delete actionSave;
    delete actionLoad;
    delete actionSaveExcel;
    delete actionLoadExcel;
    delete addRowButton;
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            if (col > 0)
                out << ",";
            out << model->data(model->index(row, col)).toString();
        }
        out << "\n";
    }
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    model->removeRows(0, model->rowCount());
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QStandardItem *> items;
        for (const QString &text : line.split(',')) {
            items.append(new QStandardItem(text));
        }
        model->appendRow(items);
    }
}

void MainWindow::addNewRow()
{
    bool ok1, ok2, ok3;
    QString text1 = QInputDialog::getText(this, tr("Input Dialog"),
                                          tr("Column 1:"), QLineEdit::Normal,
                                          "", &ok1);
    QString text2 = QInputDialog::getText(this, tr("Input Dialog"),
                                          tr("Column 2:"), QLineEdit::Normal,
                                          "", &ok2);
    QString text3 = QInputDialog::getText(this, tr("Input Dialog"),
                                          tr("Column 3:"), QLineEdit::Normal,
                                          "", &ok3);
if (ok1 && ok2 && ok3) {
    QList<QStandardItem *> items;
    items.append(new QStandardItem(text1));
    items.append(new QStandardItem(text2));
    items.append(new QStandardItem(text3));
    model->appendRow(items);
}
}

void MainWindow::saveToExcel()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Excel Files (*.xlsx)"));
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".xlsx")) {
        fileName += ".xlsx";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            if (col > 0)
                out << ",";
            out << model->data(model->index(row, col)).toString();
        }
        out << "\n";
    }
}

void MainWindow::loadFromExcel()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Excel Files (*.xlsx)"));
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".xlsx")) {
        fileName += ".xlsx";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    model->removeRows(0, model->rowCount());
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QStandardItem *> items;
        for (const QString &text : line.split(',')) {
            items.append(new QStandardItem(text));
        }
        model->appendRow(items);
    }
}
