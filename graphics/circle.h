#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    Circle(const QPoint &startPoint = QPoint(), const QPoint &endPoint = QPoint());

    void draw(QPainter *painter) override;
    ShapeType getType() const override;

    void serialize(QDataStream &out) const override;
    void deserialize(QDataStream &in) override;
};

#endif // CIRCLE_H
