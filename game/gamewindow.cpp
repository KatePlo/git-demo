#include "gamewindow.h"
#include <QPixmap>
#include <QRandomGenerator>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), teacherLives(3) {
    setFixedSize(800, 600);

    setCursor(Qt::BlankCursor);

    teacherLabel = new QLabel(this);
    QPixmap teacherPix("C:/Users/katri/OneDrive/laba3/teacher.jpg");
    teacherLabel->setPixmap(teacherPix);
    teacherLabel->setScaledContents(true);
    teacherLabel->resize(100, 100);
    teacherLabel->move(350, 250);

    batLabel = new QLabel(this);
    QPixmap batPix("C:/Users/katri/OneDrive/laba3/bat.png");
    batLabel->setPixmap(batPix);
    batLabel->setScaledContents(true);
    batLabel->resize(50, 50);

    hearseLabel = new QLabel(this);
    QPixmap hearsePix("C:/Users/katri/OneDrive/laba3/hearse.png");
    hearseLabel->setPixmap(hearsePix);
    hearseLabel->setScaledContents(true);
    hearseLabel->resize(200, 100);
    hearseLabel->move(-200, -200); // Initially off-screen

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &GameWindow::moveTeacher);
    moveTimer->start(100);
}

GameWindow::~GameWindow() {}

void GameWindow::mouseMoveEvent(QMouseEvent *event) {

    batLabel->move(event->pos() - QPoint(batLabel->width() / 2, batLabel->height() / 2));
}

void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        checkCollision();
    }
}

void GameWindow::moveTeacher() {
    if (teacherLives > 0) {
        // Получаем текущую позицию учителя
        int currentX = teacherLabel->x();
        int currentY = teacherLabel->y();

        // Определяем максимальное смещение за одно обновление
        int maxOffset = 10;

        // Генерируем новое смещение, ограниченное maxOffset
        int dx = QRandomGenerator::global()->bounded(-maxOffset, maxOffset + 1);
        int dy = QRandomGenerator::global()->bounded(-maxOffset, maxOffset + 1);

        // Новая позиция с учетом границ окна
        int newX = qBound(0, currentX + dx, this->width() - teacherLabel->width());
        int newY = qBound(0, currentY + dy, this->height() - teacherLabel->height());

        teacherLabel->move(newX, newY);
    }
}

void GameWindow::checkCollision() {
    if (batLabel->geometry().intersects(teacherLabel->geometry())) {
        teacherLives--;
        if (teacherLives == 0) {
            hearseLabel->move(teacherLabel->pos());
            teacherLabel->move(-200, -200); // Move teacher off-screen
            QTimer::singleShot(1000, this, [=]() {
                hearseLabel->move(this->width(), this->height() / 2);
            });
        } else {
            // Optionally, update teacher's appearance to show damage
            teacherLabel->setStyleSheet("background-color: rgba(255, 0, 0, 128);");
        }
    }
}
