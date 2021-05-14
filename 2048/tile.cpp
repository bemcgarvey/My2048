#include "tile.h"
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

bool Tile::merge(const Tile &t)
{
    if (t.value != value) {
        return false;
    }
    value += t.value;
    ++level;
    return true;
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


//TODO select a good set of colors
QVector<QColor> Tile::colorList = {Qt::yellow, Qt::magenta, Qt::green, Qt::blue, Qt::red, Qt::darkYellow};
QVector<QColor> Tile::fontColors = {Qt::blue, Qt::yellow, Qt::white, Qt::white, Qt::lightGray, Qt::white};
