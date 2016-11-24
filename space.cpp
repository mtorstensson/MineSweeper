#include "space.h"

/*
#include<iostream>
using namespace std;
*/

Space::Space(int x_coord, int y_coord)
    :x(x_coord), y(y_coord)
{
    if(x>=0 && y>=0)
        is_expanded = false;
    else
        is_expanded = true; //Dummy space
    mine = false;
    number = 0;
    state = -1;
    setPos(x,y);
    was_cause = false;
    still_playing = true;
}


void Space::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_expanded or !still_playing)
        return;
    if(event->button()  == Qt::LeftButton)
        if(state == -2)
            return;
        else if(mine)
        {
            was_cause = true;
            emit kaboom();
            return;
        }
        else
        {
            emit clicked(this);
            expand();
        }
    else if(event->button() == Qt::RightButton)
        mark();

}

void Space::mark()
{
    if(state==-1)
    {
        state = -2;
        emit flagged(false);
    }
    else if(state == -2)
    {
        state = -1;
        emit flagged(true);
    }
    update();
}

bool Space::is_mine()
{
    return mine;
}

void Space::is_mine(bool is_it)
{
    mine = is_it;
    return;
}

void Space::expand()
{
    // Expandera,
    if(is_expanded || state == -2)
        return;
    state = number;
    //	redraw();
    is_expanded = true;
    if(number == 0)
        for(int i=0; i < 8; i++)
            neibours[i]->expand();
    update();
    emit expanded();
}

void Space::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    char img[] = ":/images/0.png";
    switch(state)
    {
    case -99: //Om exploderat
        if(was_cause)
            img[9] = 'c';
        else
            img[9] = 'm';
        break;
    case -1:
        img[9] = 'u';// Om oklickad
        break;
    case -2:
        img[9] = 'f'; //Om flaggad
        break;
    default:
        img[9] += state;
        break;
    }

    painter->drawPixmap(0,0,IMG_X,IMG_Y,QPixmap(img));
}

void Space::setup(Space* nb[])
{
    for(int i=0; i < 8; i++)
    {
        neibours[i] = nb[i];
        if(nb[i]->is_mine())
            number++;
    }
}

bool Space::isLeft()
{
    if(state < 0 && !mine)
        return(true);
    else
        return(false);
}


QRectF Space::boundingRect() const
{
    return QRectF(0,0,IMG_X,IMG_Y);
}

void Space::explode()
{
    still_playing = false;

    if(mine)
    {
        state = -99;
        update();
    }
}

void Space::reset()
{
    is_expanded = false;
    mine = false;
    number = 0;
    state = -1;
    was_cause = false;
    still_playing = true;
    update();

}
