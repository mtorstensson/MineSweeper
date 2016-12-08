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

private:
    void createActions();
    void createMenus();


    GameBoard *board;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *newAct;
    QAction *exitAct;
    QAction *aboutAct;

};

#endif // MAINWINDOW_H
