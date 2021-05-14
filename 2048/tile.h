#ifndef TILE_H
#define TILE_H

#include <QColor>

class Tile
{
public:
    Tile(int r, int c);
    int merge(const Tile &t);
    int getValue() const {return value;}
    int getRow() const {return row;}
    int getCol() const {return col;}
    QColor getColor() const;
    QColor getFontColor() const;
    void move(int newRow, int newCol) {row = newRow; col = newCol;}
    bool operator==(const Tile &rhs) const;
private:
    int value;
    int level;
    int row;
    int col;
    static QVector<QColor> colorList;
    static QVector<QColor> fontColors;
};

#endif // TILE_H
