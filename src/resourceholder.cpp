#include "resourceholder.h"

QPixmap* ResourceHolder::black_stone_pic = NULL;
QPixmap* ResourceHolder::white_stone_pic = NULL;

ResourceHolder::ResourceHolder()
{
}

void ResourceHolder::initResource()
{
    black_stone_pic = new QPixmap(":/resources/stone_black.png");
    white_stone_pic = new QPixmap(":/resources/stone_white.png");
}

QPixmap* ResourceHolder::getBlackStone()
{
    return black_stone_pic;
}

QPixmap* ResourceHolder::getWhiteStone()
{
    return white_stone_pic;
}
