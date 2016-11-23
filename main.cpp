#include <QtWidgets>
#include "gameboard.h"
//#include "space.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    int size_x, size_y;
    GameBoard board(10,10,10,&size_x,&size_y);
    int x,y,i=0;
    int gameOn=1;
    QGraphicsView view(&board);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(Qt::gray);
//! [4] //! [5]
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "MineSweeper"));
    view.resize(size_x+10, size_y+10);
    view.show();

    //QObject::connect(&timer, SIGNAL(timeout()), &board, SLOT(advance()));

/*
    while(gameOn == 1)
    {
            cout << "Choose a space:\n";
            cin >> x >> y;
            i++;
            gameOn = board.click(x,y);
    }
    if(gameOn == 2)
            cout << "Congratulations! Only " << i << " moves!";
    else
            cout << "BOOOM!\nThat was a mine...";
    */
    return app.exec();
}

