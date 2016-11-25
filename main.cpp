#include <QtWidgets>
#include "gameboard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    int size_x, size_y;
    GameBoard board(10,10,10,&size_x,&size_y);

    QGraphicsView view(&board);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(Qt::white);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "MineSweeper"));
    view.resize(size_x+10, size_y+10);
    view.show();

    return app.exec();
}

