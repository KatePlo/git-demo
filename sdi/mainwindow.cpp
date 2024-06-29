#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *saveTextAct = new QAction(tr("Save as Text"), this);
    connect(saveTextAct, &QAction::triggered, this, &MainWindow::saveText);
    fileMenu->addAction(saveTextAct);

    QAction *loadTextAct = new QAction(tr("Load Text"), this);
    connect(loadTextAct, &QAction::triggered, this, &MainWindow::loadText);
    fileMenu->addAction(loadTextAct);

    QAction *saveBinaryAct = new QAction(tr("Save as Binary"), this);
    connect(saveBinaryAct, &QAction::triggered, this, &MainWindow::saveBinary);
    fileMenu->addAction(saveBinaryAct);

    QAction *loadBinaryAct = new QAction(tr("Load Binary"), this);
    connect(loadBinaryAct, &QAction::triggered, this, &MainWindow::loadBinary);
    fileMenu->addAction(loadBinaryAct);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::saveText() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Text"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
}

void MainWindow::loadText() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Text"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot load file: ") + file.errorString());
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();
}

void MainWindow::saveBinary() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Binary"), "", tr("Binary Files (*.bin);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QDataStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::loadBinary() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Binary"), "", tr("Binary Files (*.bin);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot load file: ") + file.errorString());
        return;
    }

    QDataStream in(&file);
    QString text;
    in >> text;
    textEdit->setPlainText(text);
    file.close();
}
