#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "shape.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"

class DrawArea : public QWidget {
    Q_OBJECT

public:
    DrawArea(QWidget *parent = nullptr);
    ~DrawArea();
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
    void setShapeType(ShapeType type);
    void setPenColor(const QColor &color);
    void setFillColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<Shape*> shapes;
    Shape *currentShape;
    ShapeType currentShapeType;
    QColor currentPenColor;
    QColor currentFillColor;

    QJsonObject shapeToJson(Shape *shape);
    Shape *shapeFromJson(const QJsonObject &json);
};

#endif // DRAWAREA_H
