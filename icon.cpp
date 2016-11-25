#include "icon.h"

Icon::Icon(int x, int y, int sizeX, int sizeY, QString playIcon, QString stopIcon, QString victoryIcon)
    :IMG_X(sizeX),IMG_Y(sizeY),play(playIcon),stop(stopIcon),victory(victoryIcon)
{
    setPos(x,y);
    active = play;
}

void Icon::reset()
{
    active = play;
    update();
}

QRectF Icon::boundingRect() const
{
    return QRectF(0,0,IMG_X,IMG_Y);
}

void Icon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,IMG_X,IMG_Y,QPixmap(active));
}

void Icon::gameEnd(bool victory)
{
    active = victory;
    update();
}

void Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()  == Qt::LeftButton)
        emit clicked();
}
