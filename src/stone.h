#ifndef STONE_H
#define STONE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Stone : public QGraphicsPixmapItem
{
public:
    enum StoneColor {
        BLACK,
        WHITE
    };

    Stone(StoneColor color);
    Stone(StoneColor color, int x, int y);
    ~Stone();

    StoneColor getColor();
    void setColor(StoneColor color);
    void setPos(int x, int y);
    void setSize(int diameter);

private:
    StoneColor color;
    int pos_x;
    int pos_y;
    static QPixmap black_stone_pic;
    static QPixmap white_stone_pic;
};

#endif // STONE_H
