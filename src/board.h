#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

class Board :
        public QGraphicsView
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent);
    ~Board();
    void drawNet();

private:
    QGraphicsScene *scene;
    QGraphicsRectItem *boardBackground;
    QList<QGraphicsLineItem *> VLines;
    QList<QGraphicsLineItem *> HLines;
    QList<QGraphicsEllipseItem *> stars;

    int boardSizePix; // board size in pixel
    int top_left_x; // board top left x coordinate in pixel
    int top_left_y; // board top left y coordinate in pixel
    int cell_width; // cell width
    int offset; // distance from board top left corner to top left stone place (x = y = offset)

    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void calculate();
    void resize();
    void drawStars();
    QPoint pointToCoordinate(int x, int y);
    QPoint coordinateToPoint(int x, int y);
};

#endif // BOARD_H
