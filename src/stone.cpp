#include "stone.h"
#include "resourceholder.h"

Stone::Stone(StoneColor color)
{
    QGraphicsPixmapItem(0);
    this->color = color;
    setColor(color);
}

Stone::Stone(StoneColor color, int x, int y)
{
    QGraphicsPixmapItem(0);
    this->color = color;
    pos_x = x;
    pos_y = y;
}

Stone::~Stone()
{

}

Stone::StoneColor Stone::getColor()
{
    return color;
}

void Stone::setColor(StoneColor color)
{
    if (color == Stone::BLACK) {
        setPixmap(*ResourceHolder::getBlackStone());
    } else if (color == Stone::WHITE) {
        setPixmap(*ResourceHolder::getWhiteStone());
    }
}

void Stone::setPos(int x, int y)
{
    QGraphicsPixmapItem::setPos((qreal)x, (qreal)y);
}

void Stone::setSize(int diameter)
{
    qreal scale = (qreal)diameter / pixmap().width();
    setScale(qreal(scale));
}
