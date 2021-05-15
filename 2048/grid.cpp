#include "grid.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QDataStream>
#include "gridsnapshot.h"

Grid::Grid(int size, int startTile) : size(size), score(0)
  , largestTile(2), moves(0), emptySpaces(size * size), undoDepth(10)
{
    for (int i = 0; i < size; ++i) {
        grid.append(QVector<Tile *>(size, nullptr));
    }
    for (int i = 0; i < startTile; ++i) {
        insertRandomTile();
    }
}

Grid::~Grid()
{
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] != nullptr) {
                delete grid[r][c];
                grid[r][c] = nullptr;
            }
        }
    }
}

bool Grid::insertRandomTile()
{
    QList<QPoint> avail = available();
    if (avail.size() == 0) {
        emptySpaces = 0;
        return false;
    }
    int v = QRandomGenerator::global()->bounded(0, avail.size());
    Tile *t = new Tile(avail[v].x(), avail[v].y());
    grid[avail[v].x()][avail[v].y()] = t;
    emptySpaces = avail.size() - 1;
    return true;
}

bool Grid::isLost() const
{
    if (emptySpaces > 0) {
        return false;
    }
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size - 1; ++c) {
            if (*grid[r][c] == *grid[r][c + 1]) {
                return false;
            }
        }
    }
    for (int c = 0; c < size; ++c) {
        for (int r = 0; r < size - 1; ++r) {
            if (*grid[r][c] == *grid[r + 1][c]) {
                return false;
            }
        }
    }
    return true;
}

QList<const Tile *> Grid::tiles() const
{
    QList<const Tile *> t;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] != nullptr) {
                t.append(grid[r][c]);
            }
        }
    }
    return t;
}

bool Grid::shift(direction dir)
{
    bool modified = false;
    GridSnapshot snap(this);
    switch (dir) {
    case shiftRight:
        for (int r = 0; r < size; ++r) {
            int limit = size - 1;
            for (int c = size - 2; c >= 0; --c) {
                if (grid[r][c] != nullptr) {
                    int newCol = c + 1;
                    while ((newCol < limit) && grid[r][newCol] == nullptr) {
                        ++newCol;
                    }
                    if (grid[r][newCol] == nullptr) {
                        grid[r][newCol] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[r][newCol]->move(r, newCol);
                        modified = true;
                    } else if(*grid[r][c] == *grid[r][newCol]) {
                        int newTileValue = grid[r][newCol]->merge(*grid[r][c]);
                        score += newTileValue;
                        if (newTileValue > largestTile) {
                            largestTile = newTileValue;
                        }
                        delete grid[r][c];
                        grid[r][c] = nullptr;
                        limit = newCol - 1;
                        modified = true;
                    } else if (newCol - 1 > c){
                        grid[r][newCol - 1] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[r][newCol - 1]->move(r, newCol - 1);
                        modified = true;
                    }
                }
            }
        }
        break;
    case shiftLeft:
        for (int r = 0; r < size; ++r) {
            int limit = 0;
            for (int c = 1; c < size; ++c) {
                if (grid[r][c] != nullptr) {
                    int newCol = c - 1;
                    while ((newCol > limit) && grid[r][newCol] == nullptr) {
                        --newCol;
                    }
                    if (grid[r][newCol] == nullptr) {
                        grid[r][newCol] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[r][newCol]->move(r, newCol);
                        modified = true;
                    } else if(*grid[r][c] == *grid[r][newCol]) {
                        int newTileValue = grid[r][newCol]->merge(*grid[r][c]);
                        score += newTileValue;
                        if (newTileValue > largestTile) {
                            largestTile = newTileValue;
                        }
                        delete grid[r][c];
                        grid[r][c] = nullptr;
                        limit = newCol + 1;
                        modified = true;
                    } else if (newCol + 1 < c){
                        grid[r][newCol + 1] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[r][newCol + 1]->move(r, newCol + 1);
                        modified = true;
                    }
                }
            }
        }
        break;
    case shiftDown:
        for (int c = 0; c < size; ++c) {
            int limit = size - 1;
            for (int r = size - 2; r >= 0; --r) {
                if (grid[r][c] != nullptr) {
                    int newRow = r + 1;
                    while ((newRow < limit) && grid[newRow][c] == nullptr) {
                        ++newRow;
                    }
                    if (grid[newRow][c] == nullptr) {
                        grid[newRow][c] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[newRow][c]->move(newRow, c);
                        modified = true;
                    } else if(*grid[r][c] == *grid[newRow][c]) {
                        int newTileValue = grid[newRow][c]->merge(*grid[r][c]);
                        score += newTileValue;
                        if (newTileValue > largestTile) {
                            largestTile = newTileValue;
                        }
                        delete grid[r][c];
                        grid[r][c] = nullptr;
                        limit = newRow - 1;
                        modified = true;
                    } else if (newRow - 1 > r){
                        grid[newRow - 1][c] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[newRow - 1][c]->move(newRow - 1, c);
                        modified = true;
                    }
                }
            }
        }
        break;
    case shiftUp:
        for (int c = 0; c < size; ++c) {
            int limit = 0;
            for (int r = 1; r < size; ++r) {
                if (grid[r][c] != nullptr) {
                    int newRow = r - 1;
                    while ((newRow > limit) && grid[newRow][c] == nullptr) {
                        --newRow;
                    }
                    if (grid[newRow][c] == nullptr) {
                        grid[newRow][c] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[newRow][c]->move(newRow, c);
                        modified = true;
                    } else if(*grid[r][c] == *grid[newRow][c]) {
                        int newTileValue = grid[newRow][c]->merge(*grid[r][c]);
                        score += newTileValue;
                        if (newTileValue > largestTile) {
                            largestTile = newTileValue;
                        }
                        delete grid[r][c];
                        grid[r][c] = nullptr;
                        limit = newRow + 1;
                        modified = true;
                    } else if (newRow + 1 < r){
                        grid[newRow + 1][c] = grid[r][c];
                        grid[r][c] = nullptr;
                        grid[newRow + 1][c]->move(newRow + 1, c);
                        modified = true;
                    }
                }
            }
        }
        break;
    }
    if (modified) {
        ++moves;
        insertRandomTile();
        if (undoStack.size() < undoDepth) {
            undoStack.push_front(snap);
        } else {
            undoStack.pop_back();
            undoStack.push_front(snap);
        }
    }
    return modified;
}

void Grid::getStats(int &score, int &moves, int &largestTile) const
{
    score = this->score;
    moves = this->moves;
    largestTile = this->largestTile;
}

bool Grid::undo()
{
    if (undoStack.empty()) {
        return false;
    }
    GridSnapshot &u = undoStack.front();
    size = u.size;
    score = u.score;
    moves = u.moves;
    largestTile = u.largestTile;
    emptySpaces = u.emptySpaces;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] != nullptr) {
                delete grid[r][c];
            }
            grid[r][c] = nullptr;
        }
    }
    for (auto &&i : u.tiles) {
        Tile *t = new Tile(i);
        grid[t->getRow()][t->getCol()] = t;
    }
    undoStack.pop_front();
    return true;
}

QList<QPoint> Grid::available() const
{
    QList<QPoint> spaces;
    spaces.empty();
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c] == nullptr) {
                spaces.append(QPoint(r, c));
            }
        }
    }
    return spaces;
}

QDataStream& operator<<(QDataStream &stream, const Grid &g) {
    stream << g.size << g.score << g.moves << g.largestTile << g.undoDepth;
    stream << ((g.size * g.size) - g.emptySpaces);
    for (int r = 0; r < g.size; ++r) {
        for (int c = 0; c < g.size; ++c) {
            if (g.grid[r][c] != nullptr) {
                stream << *(g.grid[r][c]);
            }
        }
    }
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Grid &g) {
    stream >> g.size >> g.score >> g.moves >> g.largestTile >> g.undoDepth;
    int numTiles;
    stream >> numTiles;
    for (int r = 0; r < g.size; ++r) {
        for (int c = 0; c < g.size; ++c) {
            if (g.grid[r][c] != nullptr) {
                delete g.grid[r][c];
            }
            g.grid[r][c] = nullptr;
        }
    }
    for (int i = 0; i < numTiles; ++i) {
        Tile *t;
        t = new Tile(0, 0);
        stream >> *t;
        g.grid[t->getRow()][t->getCol()] = t;
    }
    g.undoStack.clear();
    return stream;
}
