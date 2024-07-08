#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moveTeacher();

private:
    QLabel *teacherLabel;
    QLabel *batLabel;
    QLabel *hearseLabel;
    QTimer *moveTimer;
    int teacherLives;
    void checkCollision();
};

#endif // GAMEWINDOW_H
