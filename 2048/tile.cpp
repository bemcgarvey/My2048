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

//TODO select a good set of colors
QVector<QColor> Tile::colorList = {Qt::yellow, Qt::magenta, Qt::green, Qt::blue, Qt::red, Qt::darkYellow, QColor(128, 128, 128), QColor(36, 250, 198)};
QVector<QColor> Tile::fontColors = {Qt::blue, Qt::yellow, Qt::white, Qt::white, Qt::lightGray, Qt::white};
