#include "line.h"

Line::Line(const QPoint &startPoint, const QPoint &endPoint)
    : Shape(startPoint, endPoint) {
}

void Line::draw(QPainter *painter) {
    painter->setPen(QPen(penColor, 1));
    painter->drawLine(startPoint, endPoint);
}

ShapeType Line::getType() const {
    return LineType;
}

void Line::serialize(QDataStream &out) const {
    Shape::serialize(out);
    out << static_cast<int>(getType());
}

void Line::deserialize(QDataStream &in) {
    Shape::deserialize(in);
}
