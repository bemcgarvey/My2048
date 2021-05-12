#ifndef TILE_H
#define TILE_H

#include <QColor>
#include <QPoint>

class Tile
{
public:
    Tile(QPoint pos);
    bool merge(const Tile &t);
    int getValue() const {return value;}
    QPoint getPosition() const {return pos;}
    QColor getColor();
    void move(QPoint newPos) {pos = newPos;}
private:
    int value;
    QPoint pos;
    static QVector<QColor> colorList_;
};

#endif // TILE_H
