#include "tile.h"
#include <QRandomGenerator>

Tile::Tile(QPoint pos)
{
    this->pos = pos;
    int v = QRandomGenerator::global()->bounded(0, 9);
    if (v == 9) {
        value = 4;
    } else {
        value = 2;
    }
}

bool Tile::merge(const Tile &t)
{
    if (t.value != value) {
        return false;
    }
    value += t.value;
    return true;
}

QColor Tile::getColor()
{
    int p = 0;
    int v = value;
    while (v > 2) {
        v /= 2;
        ++p;
    }
    if (p >= colorList_.size()) {
        return Qt::white;
    } else {
        return colorList_[p];
    }
}

QVector<QColor> Tile::colorList_ = {Qt::white, Qt::yellow, Qt::green, Qt::blue, Qt::red, Qt::lightGray};
