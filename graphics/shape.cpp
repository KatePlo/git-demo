#include "shape.h"

Shape::Shape(const QPoint &startPoint, const QPoint &endPoint)
    : startPoint(startPoint), endPoint(endPoint), penColor(Qt::black), fillColor(Qt::white), filled(false) {
}

QPoint Shape::getStartPoint() const {
    return startPoint;
}

QPoint Shape::getEndPoint() const {
    return endPoint;
}

QColor Shape::getPenColor() const {
    return penColor;
}

QColor Shape::getFillColor() const {
    return fillColor;
}

bool Shape::isFilled() const {
    return filled;
}

void Shape::setStartPoint(const QPoint &point) {
    startPoint = point;
}

void Shape::setEndPoint(const QPoint &point) {
    endPoint = point;
}

void Shape::setPenColor(const QColor &color) {
    penColor = color;
}

void Shape::setFillColor(const QColor &color) {
    fillColor = color;
}

void Shape::setFilled(bool filled) {
    this->filled = filled;
}

void Shape::serialize(QDataStream &out) const {
    out << startPoint << endPoint << penColor << fillColor << filled;
}

void Shape::deserialize(QDataStream &in) {
    in >> startPoint >> endPoint >> penColor >> fillColor >> filled;
}
