#include "board.h"
#include <QGraphicsLineItem>

#define BOARD_SIZE 19

Board::Board(QWidget *)
{
    scene = new QGraphicsScene(0, 0, 200, 200, this);
    scene->setBackgroundBrush(QBrush(QColor(0, 100, 0)));
    boardBackground = scene->addRect(QRectF(0, 0, 100, 100), QPen(Qt::NoPen), QBrush(*(new QPixmap(":/resources/wood.png"))));
    setScene(scene);

    // init lines
    for(int i=0; i<BOARD_SIZE; i++) {
        QGraphicsLineItem *itemH = new QGraphicsLineItem;
        HLines.append(itemH);
        scene->addItem(itemH);

        QGraphicsLineItem *itemV = new QGraphicsLineItem;
        VLines.append(itemV);
        scene->addItem(itemV);
    }

    // init stars
    for (int i=0; i<9; i++) {
        QGraphicsEllipseItem *item = new QGraphicsEllipseItem(0);
        item->setBrush(Qt::SolidPattern);
        item->setPen(Qt::NoPen);
        scene->addItem(item);
        stars.append(item);
    }
}

Board::~Board()
{
    qDeleteAll(stars);
    qDeleteAll(VLines);
    qDeleteAll(HLines);
    delete scene;
}

void Board::resizeEvent(QResizeEvent *)
{
    resize();
}

void Board::keyPressEvent(QKeyEvent *event)
{

}

void Board::calculate()
{
    int max_height = height();
    int max_width = width();

    boardSizePix = max_height < max_width ? max_height : max_width; // board size in pixel

    top_left_x = (max_width - boardSizePix) / 2; // board top left x coordinate
    top_left_y = (max_height - boardSizePix) / 2; // board top left y coordinate

    boardBackground->setRect(QRectF(top_left_x, top_left_y, boardSizePix, boardSizePix));

    cell_width = (boardSizePix - (boardSizePix % BOARD_SIZE)) / BOARD_SIZE;

    offset = (cell_width + boardSizePix % BOARD_SIZE) / 2; // distance from board top left to top left stone place offset
}

void Board::resize()
{
    setSceneRect(0, 0, width(), height());
    calculate();
    drawNet();
    qInfo("board resize width: %d, height: %d", width(), height());
}

void Board::drawNet()
{
    // draw horizontal lines
    QList<QGraphicsLineItem *>::iterator iteH = HLines.begin();
    for (int i=0; iteH != HLines.end(); i++, iteH++) {
        (*iteH)->setLine(offset + top_left_x, offset + top_left_y + i * cell_width,
                       offset + top_left_x + boardSizePix - 2 * offset, offset + top_left_y + i * cell_width);
    }

    // draw vertial lines
    QList<QGraphicsLineItem *>::iterator iteV = VLines.begin();
    for (int i=0; iteV != VLines.end(); i++, iteV++) {
        (*iteV)->setLine(offset + top_left_x + i * cell_width, offset + top_left_y,
                       offset + top_left_x + i * cell_width, offset + top_left_y + boardSizePix - 2 * offset);
    }

    drawStars();
}

void Board::drawStars()
{
    // star points
    static int starPoints[][2] = {{3,3}, {3,9}, {3,15},
                                  {9,3}, {9,9}, {9,15},
                                  {15,3}, {15,9}, {15,15}};

    int starRadius = cell_width / 8;

    QList<QGraphicsEllipseItem *>::iterator ite = stars.begin();
    for (int i=0; ite != stars.end(); i++, ite++) {
        QPoint point = pointToCoordinate(starPoints[i][0], starPoints[i][1]);
        (*ite)->setRect(point.x() - starRadius, point.y() - starRadius, 2 * starRadius, 2 * starRadius);
    }
}

QPoint Board::pointToCoordinate(int x, int y)
{
    return QPoint(top_left_x + offset + x * cell_width, top_left_y + offset + y * cell_width);
}

QPoint Board::coordinateToPoint(int x, int y)
{
    return QPoint((x - top_left_x - offset) / cell_width, (y - top_left_y - offset) / cell_width);
}
