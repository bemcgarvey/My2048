#include "grid.h"
#include <QRandomGenerator>
#include <QDebug>

Grid::Grid(int size, int startTile) : size(size)
{
    for (int i = 0; i < size; ++i) {
        grid.append(QVector<Tile *>(size, nullptr));
    }
    for (int i = 0; i < startTile; ++i) {
        insertRandomTile();
    }
}

bool Grid::insertRandomTile()
{
    auto avail = available();
    if (avail.size() == 0) {
        return false;
    }
    int v = QRandomGenerator::global()->bounded(0, avail.size());
    Tile *t = new Tile(avail[v]);
    grid[avail[v].x()][avail[v].y()] = t;
    return true;
}

bool Grid::hasAvailable() const
{
    return available().size() > 0;
}

QList<const Tile *> Grid::tiles() const
{
    QList<const Tile *> t;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            t.append(grid[r][c]);
        }
    }
    return t;
}

QList<QPoint> Grid::available() const
{
    QList<QPoint> spaces;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] == nullptr) {
                spaces.append(QPoint(r, c));
            }
        }
    }
    return spaces;
}
