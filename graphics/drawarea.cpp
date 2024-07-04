#include "drawarea.h"
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>

DrawArea::DrawArea(QWidget *parent)
    : QWidget(parent), currentShape(nullptr), currentShapeType(LineType), currentPenColor(Qt::black), currentFillColor(Qt::white) {
}

DrawArea::~DrawArea() {
    qDeleteAll(shapes);
}

void DrawArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(currentPenColor, 1));
    for (Shape *shape : shapes) {
        shape->draw(&painter);
    }
    if (currentShape) {
        currentShape->draw(&painter);
    }
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
    switch (currentShapeType) {
    case LineType:
        currentShape = new Line(event->pos());
        break;
    case RectangleType:
        currentShape = new Rectangle(event->pos());
        break;
    case CircleType:
        currentShape = new Circle(event->pos());
        break;
    }
    if (currentShape) {
        currentShape->setPenColor(currentPenColor);
        currentShape->setFillColor(currentFillColor);
        currentShape->setFilled(true);
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    if (currentShape) {
        currentShape->setEndPoint(event->pos());
        update();
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event) {
    if (currentShape) {
        currentShape->setEndPoint(event->pos());
        shapes.append(currentShape);
        currentShape = nullptr;
        update();
    }
}

void DrawArea::saveToFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonArray shapesArray;
        for (Shape *shape : shapes) {
            QJsonObject shapeObject = shapeToJson(shape);
            shapesArray.append(shapeObject);
        }
        QJsonObject saveObject;
        saveObject["shapes"] = shapesArray;

        QJsonDocument saveDoc(saveObject);
        file.write(saveDoc.toJson());
        file.close();
    }
}

void DrawArea::loadFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to open file."));
        return;
    }

    QByteArray loadData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject loadObject = loadDoc.object();

    if (loadObject.contains("shapes") && loadObject["shapes"].isArray()) {
        qDeleteAll(shapes);
        shapes.clear();

        QJsonArray shapesArray = loadObject["shapes"].toArray();
        for (const QJsonValue &shapeValue : shapesArray) {
            if (shapeValue.isObject()) {
                QJsonObject shapeObject = shapeValue.toObject();
                Shape *shape = shapeFromJson(shapeObject);
                if (shape) {
                    shapes.append(shape);
                }
            }
        }

        update();
    }
}

void DrawArea::setShapeType(ShapeType type) {
    currentShapeType = type;
}

void DrawArea::setPenColor(const QColor &color) {
    currentPenColor = color;
    if (currentShape) {
        currentShape->setPenColor(currentPenColor);
    }
}

void DrawArea::setFillColor(const QColor &color) {
    currentFillColor = color;
    if (currentShape) {
        currentShape->setFillColor(currentFillColor);
    }
}

QJsonObject DrawArea::shapeToJson(Shape *shape) {
    QJsonObject shapeObject;
    shapeObject["type"] = static_cast<int>(shape->getType());
    shapeObject["startX"] = shape->getStartPoint().x();
    shapeObject["startY"] = shape->getStartPoint().y();
    shapeObject["endX"] = shape->getEndPoint().x();
    shapeObject["endY"] = shape->getEndPoint().y();
    shapeObject["penColor"] = shape->getPenColor().name(QColor::HexRgb);
    shapeObject["fillColor"] = shape->getFillColor().name(QColor::HexRgb);
    shapeObject["filled"] = shape->isFilled();

    return shapeObject;
}
Shape *DrawArea::shapeFromJson(const QJsonObject &json) {
    ShapeType type = static_cast<ShapeType>(json["type"].toInt());
    QPoint start(json["startX"].toInt(), json["startY"].toInt());
    QPoint end(json["endX"].toInt(), json["endY"].toInt());
    QColor penColor(json["penColor"].toString());
    QColor fillColor(json["fillColor"].toString());
    bool filled = json["filled"].toBool();

    Shape *shape = nullptr;
    switch (type) {
    case LineType:
        shape = new Line(start, end);
        break;
    case RectangleType:
        shape = new Rectangle(start, end);
        break;
    case CircleType:
        shape = new Circle(start, end);
        break;
    }

    if (shape) {
        shape->setPenColor(penColor);
        shape->setFillColor(fillColor);
        shape->setFilled(filled);
    }

    return shape;
}
