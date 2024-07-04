#include "mainwindow.h"
#include "drawarea.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QToolBar>
#include <QActionGroup>
#include <QAction>
#include <QColorDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), drawArea(new DrawArea(this)) {
    setCentralWidget(drawArea);
    resize(800, 600);

    // Создание меню File
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *saveAction = fileMenu->addAction(tr("&Save as Text"));
    QAction *loadAction = fileMenu->addAction(tr("&Load from Text"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveAsText);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadFromText);

    // Создание панели инструментов для выбора типа фигуры
    QToolBar *toolbar = addToolBar(tr("Shapes"));
    QActionGroup *shapeGroup = new QActionGroup(this);

    QAction *lineAction = toolbar->addAction(tr("Line"));
    lineAction->setCheckable(true);
    lineAction->setChecked(true);
    shapeGroup->addAction(lineAction);
    connect(lineAction, &QAction::triggered, this, &MainWindow::setLineShape);

    QAction *rectangleAction = toolbar->addAction(tr("Rectangle"));
    rectangleAction->setCheckable(true);
    shapeGroup->addAction(rectangleAction);
    connect(rectangleAction, &QAction::triggered, this, &MainWindow::setRectangleShape);

    QAction *circleAction = toolbar->addAction(tr("Circle"));
    circleAction->setCheckable(true);
    shapeGroup->addAction(circleAction);
    connect(circleAction, &QAction::triggered, this, &MainWindow::setCircleShape);

    // Создание панели инструментов для выбора цвета
    QToolBar *colorToolbar = addToolBar(tr("Color"));
    QAction *penColorAction = colorToolbar->addAction(tr("Pen Color"));
    connect(penColorAction, &QAction::triggered, this, &MainWindow::setPenColor);

    QAction *fillColorAction = colorToolbar->addAction(tr("Fill Color"));
    connect(fillColorAction, &QAction::triggered, this, &MainWindow::setFillColor);
}

MainWindow::~MainWindow() {
}

void MainWindow::setLineShape() {
    drawArea->setShapeType(LineType);
}

void MainWindow::setRectangleShape() {
    drawArea->setShapeType(RectangleType);
}

void MainWindow::setCircleShape() {
    drawArea->setShapeType(CircleType);
}

void MainWindow::setPenColor() {
    QColor color = QColorDialog::getColor(Qt::black, this, tr("Choose Pen Color"));
    if (color.isValid()) {
        drawArea->setPenColor(color);
    }
}

void MainWindow::setFillColor() {
    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Fill Color"));
    if (color.isValid()) {
        drawArea->setFillColor(color);
    }
}

void MainWindow::saveAsText() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File as Text"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        drawArea->saveToFile(fileName);
    }
}

void MainWindow::loadFromText() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load File from Text"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        drawArea->loadFromFile(fileName);
    }
}
