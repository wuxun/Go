#ifndef RESOURSEHOLDER_H
#define RESOURSEHOLDER_H

#include <QPixmap>

class ResourceHolder
{
public:
    static void initResource();
    static QPixmap* getBlackStone();
    static QPixmap* getWhiteStone();

private:
    ResourceHolder();
    static QPixmap *black_stone_pic;
    static QPixmap *white_stone_pic;
};

#endif // RESOURSEHOLDER_H
