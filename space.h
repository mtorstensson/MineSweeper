#ifndef SPACE_H
#define SPACE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include <math.h>


//! [0]
class Space : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Space(int x, int y);

    void mark(); //Om den markeras som mina
    bool is_mine();
    void is_mine(bool is_it);
    void expand();
    //void redraw();
    void setup(Space* nb[]);
    bool isLeft();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

public slots:
    void explode();
    void reset();

signals:
    void kaboom();
    void clicked(Space* origin);
    void flagged(bool unflag);
    void expanded();
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    const int IMG_X = 30;
    const int IMG_Y = 30;
    bool mine;
    bool is_expanded;
    bool still_playing;
    bool was_cause;
    int number;
    Space* neibours[8];
    int state;
    int x;
    int y;
};
//! [0]

#endif
