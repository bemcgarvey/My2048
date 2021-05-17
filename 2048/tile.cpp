#include "tile.h"
#include <QDataStream>
#include <QRandomGenerator>

Tile::Tile(int r, int c) : row(r), col(c)
{
    int v = QRandomGenerator::global()->bounded(0, 10);
    if (v == 9) {
        value = 4;
        level = 1;
    } else {
        value = 2;
        level = 0;
    }
}

int Tile::merge(const Tile &t)
{
    if (t.value != value) {
        return false;
    }
    value += t.value;
    ++level;
    return value;
}

QColor Tile::getColor() const
{
    if (level >= colorList.size()) {
        return Qt::white;
    } else {
        return colorList[level];
    }
}

QColor Tile::getFontColor() const
{
    if (level >= fontColors.size()) {
        return Qt::black;
    } else {
        return fontColors[level];
    }
}

bool Tile::operator==(const Tile &rhs) const
{
    return value == rhs.value;
}

QDataStream& operator<<(QDataStream &stream, const Tile &t) {
    stream << t.value << t.level << t.row << t.col;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Tile &t) {
    stream >> t.value >> t.level >> t.row >> t.col;
    return stream;
}

QVector<QColor> Tile::colorList = {Qt::yellow, Qt::magenta, Qt::green, Qt::blue, Qt::red, QColor(73, 225, 138)
                                   , QColor(230, 27, 218), QColor(241, 180, 16), QColor(173, 83, 171)
                                   , QColor(34, 216, 223), QColor(87, 96, 211)};
QVector<QColor> Tile::fontColors = {Qt::blue, Qt::yellow, Qt::white, Qt::yellow, Qt::black, Qt::white
                                   , Qt::black, Qt::white, Qt::red, Qt::white, Qt::yellow};
