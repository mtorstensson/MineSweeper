#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsScene>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "space.h"
#include "counter.h"

class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    GameBoard(int x=10, int y=10, int n_mines=10);
    GameBoard(int x, int y, int n_mines, int *size_x, int *size_y);
    ~GameBoard();
    void start(int x, int y, int n_mines);
    bool emptyLeft();

protected:
    void setup(Space* first);

public slots:
    void hit_mine();
    void move_made(Space* clicked);
    void checkDone();

signals:
    void kaboom();
    void restart();

private:
    const int IMG_X = 33;
    const int IMG_Y = 33;
    Space* spaces[100];
    Space* dummy;
    Counter* timeCounter;
    Counter* mineCounter;
    int x_max, y_max,mines,empty;
    bool state, first;
    int moves_made;
    QTimer* timer;

};

#endif // GAMEBOARD_H
