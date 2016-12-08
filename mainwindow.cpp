#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    int size_x, size_y;
    board = new GameBoard(16,16,40,&size_x,&size_y);
    connect(board,SIGNAL(gameStarts()),this,SLOT(start()));
    connect(board,SIGNAL(moves(int)),this,SLOT(moves(int)));
    QGraphicsView *view = new QGraphicsView(board);
    setCentralWidget(view);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(Qt::lightGray);

    createActions();
    createMenus();

    QString message = tr("Take a guess!");
    statusBar()->showMessage(message);

    setWindowTitle(tr("MineSweeper"));
    size_x += 20;
    size_y += 70;
    setMinimumSize(size_x, size_y);
    resize(size_x, size_y);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Minesweeper"),
            tr("This MineSweeper clone is made by  "
               "<b>Martin Torstensson</b>."));
}

void MainWindow::start()
{
    QString message = tr("The game is afoot!");
    statusBar()->showMessage(message);
}

void MainWindow::moves(int m)
{
    QString message = tr("Number of moves: %i");
    statusBar()->showMessage(message);
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), board, SLOT(reset()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
