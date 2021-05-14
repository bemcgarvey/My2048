#include "gridframe.h"
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

GridFrame::GridFrame(QWidget *parent) : QFrame(parent), grid(nullptr)
{
    grabKeyboard();
}

GridFrame::~GridFrame()
{
    delete grid;
}

void GridFrame::setGrid(Grid *grid)
{
    if (this->grid != nullptr) {
        delete this->grid;
        this->grid = nullptr;
    }
    this->grid = grid;
}


void GridFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    if (grid == nullptr) {
        return;
    }
    QPainter painter(this);
    QPen pen(Qt::lightGray, borderWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(leftBorder + borderWidth / 2, borderWidth / 2, gridSize - borderWidth, gridSize - borderWidth);
    for (int c = 0, i = borderWidth / 2; c < grid->getSize(); i += (tileSize + borderWidth), ++c) {
        painter.drawLine(leftBorder + i, 0, leftBorder + i, gridSize);
        painter.drawLine(leftBorder, i, leftBorder + gridSize, i);
    }
    auto tiles = grid->tiles();
    QPen pen2(Qt::black, 1);
    QBrush brush(Qt::black);
    for (auto &&i : tiles) {
        pen2.setColor(i->getColor());
        brush.setColor(i->getColor());
        painter.setPen(pen2);
        painter.setBrush(brush);
        int r = i->getRow();
        int c = i->getCol();
        QRect rect(leftBorder + borderWidth + c * (borderWidth + tileSize)
                   , borderWidth + r * (borderWidth + tileSize), tileSize, tileSize);
        painter.drawRect(rect);
        QFont font = painter.font();
        if (i->getValue() < 10) {
            font.setPixelSize(tileSize * 0.9);
        } else if (i->getValue() < 100) {
            font.setPixelSize(tileSize * 0.67);
        }
        pen2.setColor(i->getFontColor());
        painter.setPen(pen2);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(i->getValue()));
    }
}


QSize GridFrame::sizeHint() const
{
    return QSize(300, 300);
}


void GridFrame::resizeEvent(QResizeEvent *event)
{
    if (grid == nullptr) {
        return;
    }
    if (event->size().width() > event->size().height()) {
        gridSize = event->size().height();
    } else {
        gridSize = event->size().width();
    }
    int borders = borderWidth * (grid->getSize() + 1);
    int extra = (gridSize - borders) % grid->getSize();
    gridSize -= extra;
    leftBorder = (event->size().width() - gridSize) / 2;
    tileSize = gridSize - (borderWidth * (grid->getSize() + 1));
    tileSize /= grid->getSize();
}



void GridFrame::keyPressEvent(QKeyEvent *event)
{
    bool success = false;
    if (event->key() == Qt::Key_Left) {
        success = grid->shift(Grid::shiftLeft);
    } else if (event->key() == Qt::Key_Right) {
        success = grid->shift(Grid::shiftRight);
    } else if (event->key() == Qt::Key_Up) {
        success = grid->shift(Grid::shiftUp);
    } else if (event->key() == Qt::Key_Down) {
        success = grid->shift(Grid::shiftDown);
    }
    if (success) {
        grid->insertRandomTile();
        update();
    }
    event->accept();
}