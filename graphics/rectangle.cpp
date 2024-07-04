#include "rectangle.h"

Rectangle::Rectangle(const QPoint &startPoint, const QPoint &endPoint)
    : Shape(startPoint, endPoint) {
}

void Rectangle::draw(QPainter *painter) {
    QPen pen(penColor, 1);
    painter->setPen(pen);
    QRect rect(startPoint, endPoint);
    if (filled) {
        painter->setBrush(QBrush(fillColor));
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(rect);
}

ShapeType Rectangle::getType() const {
    return RectangleType;
}

void Rectangle::serialize(QDataStream &out) const {
    Shape::serialize(out);
    out << static_cast<int>(getType());
}

void Rectangle::deserialize(QDataStream &in) {
    Shape::deserialize(in);
}
