#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем элементы интерфейса
    input1 = new QLineEdit(this);
    input2 = new QLineEdit(this);
    QPushButton *calculateButton = new QPushButton("Рассчитать", this);
    resultLabel = new QLabel(this);

    // Создаем компоновщик и добавляем элементы
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(input1);
    layout->addWidget(input2);
    layout->addWidget(calculateButton);
    layout->addWidget(resultLabel);

    // Подключаем сигнал от кнопки к слоту
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);
}

MainWindow::~MainWindow()
{
}

double MainWindow::calculate(double value1, double value2)
{
    return value1 + value2;  // Пример простой расчетной функции
}

void MainWindow::on_calculateButton_clicked()
{
    bool ok1, ok2;
    double value1 = input1->text().toDouble(&ok1);
    double value2 = input2->text().toDouble(&ok2);

    if (ok1 && ok2) {
        double result = calculate(value1, value2);
        resultLabel->setText(QString::number(result));
    } else {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные числа.");
    }
}
