#include "circle.h"
#include <cmath>

Circle::Circle(const QPoint &startPoint, const QPoint &endPoint)
    : Shape(startPoint, endPoint) {
}

void Circle::draw(QPainter *painter) {
    QPen pen(penColor, 1);
    painter->setPen(pen);
    int radius = std::sqrt(std::pow(endPoint.x() - startPoint.x(), 2) +
                           std::pow(endPoint.y() - startPoint.y(), 2));
    if (filled) {
        painter->setBrush(QBrush(fillColor));
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawEllipse(startPoint, radius, radius);
}

ShapeType Circle::getType() const {
    return CircleType;
}

void Circle::serialize(QDataStream &out) const {
    Shape::serialize(out);
    out << static_cast<int>(getType());
}

void Circle::deserialize(QDataStream &in) {
    Shape::deserialize(in);
}
