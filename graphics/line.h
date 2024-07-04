#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape {
public:
    Line(const QPoint &startPoint = QPoint(), const QPoint &endPoint = QPoint());

    void draw(QPainter *painter) override;
    ShapeType getType() const override;

    void serialize(QDataStream &out) const override;
    void deserialize(QDataStream &in) override;
};

#endif // LINE_H
