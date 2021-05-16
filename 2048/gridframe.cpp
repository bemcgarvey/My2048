#include "gridframe.h"
#include <QPainter>
#include <QResizeEvent>

GridFrame::GridFrame(QWidget *parent) : QFrame(parent), grid(nullptr)
{
    grabKeyboard();
    setAttribute(Qt::WA_AcceptTouchEvents);
}

GridFrame::~GridFrame()
{
}

void GridFrame::setGrid(Grid *g)
{
    grid = std::unique_ptr<Grid>(g);
}

void GridFrame::undo()
{
    if (grid->undo()) {
        int score;
        int moves;
        int largestTile;
        grid->getStats(score, moves, largestTile);
        emit scoreUpdate(score, moves, largestTile);
        update();
    }
}

void GridFrame::saveGrid(QDataStream &out)
{
    out << *grid;
}

void GridFrame::loadGrid(QDataStream &in)
{
    in >> *grid;
    int score;
    int moves;
    int largestTile;
    grid->getStats(score, moves, largestTile);
    emit scoreUpdate(score, moves, largestTile);
    update();
}


void GridFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    if (!grid) {
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
        QRect rect(leftBorder + 1 + borderWidth + c * (borderWidth + tileSize)
                   , borderWidth + 1 + r * (borderWidth + tileSize), tileSize - 2, tileSize - 2);
        painter.drawRoundedRect(rect, 30, 30, Qt::RelativeSize);
        QFont font = painter.font();
        if (i->getValue() < 10) {
            font.setPixelSize(tileSize * 0.9);
        } else if (i->getValue() < 100) {
            font.setPixelSize(tileSize * 0.67);
        } else if (i->getValue() < 1000) {
            font.setPixelSize(tileSize * 0.5);
        } else {
            font.setPixelSize(tileSize * 0.4);
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
    if (!grid) {
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
    if (event->key() == Qt::Key_Left) {
        shiftGrid(Grid::shiftLeft);
    } else if (event->key() == Qt::Key_Right) {
        shiftGrid(Grid::shiftRight);
    } else if (event->key() == Qt::Key_Up) {
        shiftGrid(Grid::shiftUp);
    } else if (event->key() == Qt::Key_Down) {
        shiftGrid(Grid::shiftDown);
    }
    event->accept();
}


bool GridFrame::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
        break;
    case QEvent::TouchEnd:
    {
        QTouchEvent *te = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = te->touchPoints();
        if (touchPoints.size() == 1) {
            const QTouchEvent::TouchPoint& tp = touchPoints[0];
            int x = tp.lastPos().x() - tp.startPos().x();
            int y = tp.lastPos().y() - tp.startPos().y();
            if (abs(x) > abs(y)) {
                if (x > 0) {
                    shiftGrid(Grid::shiftRight);
                } else {
                    shiftGrid(Grid::shiftLeft);
                }
            } else {
                if (y > 0) {
                    shiftGrid(Grid::shiftDown);
                } else {
                    shiftGrid(Grid::shiftUp);
                }
            }
        }
        break;
    }
    default:
        return QFrame::event(event);
    }
    return true;
}

void GridFrame::shiftGrid(Grid::Direction dir)
{
    bool success = grid->shift(dir);
    if (success) {
        update();
    }
    int score;
    int moves;
    int largestTile;
    grid->getStats(score, moves, largestTile);
    emit scoreUpdate(score, moves, largestTile);
    if (grid->isLost()) {
        emit lostGame();
    }
}
