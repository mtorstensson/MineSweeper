#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    void newFile();
    

public slots:
    void start();
    void moves(int m);
    void about();
    void smallBoard();
    void mediumBoard();
    void largeBoard();

private:
    void createActions();
    void createMenus();
    void setup(int x,int y, int mines);


    GameBoard *board;
    QGraphicsView *view;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *sizeMenu;
    QActionGroup *boardSize;
    QAction *newAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *smallSize;
    QAction *mediumSize;
    QAction *largeSize;

};

#endif // MAINWINDOW_H
