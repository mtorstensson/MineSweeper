#ifndef ICON_H
#define ICON_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Icon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:   
    Icon(int x=0, int y=0, int sizeX=100, int sizeY=100, QString playIcon=":/images/play.png", QString stopIcon=":/images/stop.png", QString victoryIcon=":/images/victory.png");


    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

public slots:
    void gameEnd(bool victory);
    void reset();

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QString active,play,stop,victory;
    int IMG_X,IMG_Y;
};

#endif // ICON_H
