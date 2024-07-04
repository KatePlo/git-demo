#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const QPoint &startPoint = QPoint(), const QPoint &endPoint = QPoint());

    void draw(QPainter *painter) override;
    ShapeType getType() const override;

    void serialize(QDataStream &out) const override;
    void deserialize(QDataStream &in) override;
};

#endif // RECTANGLE_H
