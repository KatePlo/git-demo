#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QDataStream>

enum ShapeType {
    LineType,
    RectangleType,
    CircleType
};

class Shape {
public:
    Shape(const QPoint &startPoint, const QPoint &endPoint = QPoint());
    virtual ~Shape() = default;

    virtual void draw(QPainter *painter) = 0;
    virtual ShapeType getType() const = 0;

    QPoint getStartPoint() const;
    QPoint getEndPoint() const;
    QColor getPenColor() const;
    QColor getFillColor() const;
    bool isFilled() const;

    void setStartPoint(const QPoint &point);
    void setEndPoint(const QPoint &point);
    void setPenColor(const QColor &color);
    void setFillColor(const QColor &color);
    void setFilled(bool filled);

    virtual void serialize(QDataStream &out) const;
    virtual void deserialize(QDataStream &in);

protected:
    QPoint startPoint;
    QPoint endPoint;
    QColor penColor;
    QColor fillColor;
    bool filled;
};

#endif // SHAPE_H
