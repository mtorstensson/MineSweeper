#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setup(9,9,10);
    createActions();
    createMenus();

    setWindowTitle(tr("MineSweeper"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Minesweeper"),
            tr("This MineSweeper clone is made by  "
               "<b>Martin Torstensson</b>."));
}

void MainWindow::smallBoard()
{
    delete board;
    delete view;
    setup(9,9,10);
}

void MainWindow::mediumBoard()
{
    delete board;
    delete view;
    setup(16,16,40);
}

void MainWindow::largeBoard()
{
    delete board;
    delete view;
    setup(30,16,99);
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

    smallSize = new QAction(tr("Small board (9x9 spaces, 10 mines)"),this);
    smallSize->setCheckable(true);
    connect(smallSize,SIGNAL(triggered()),this, SLOT(smallBoard()));

    mediumSize = new QAction(tr("Medium board (16x16 spaces, 40 mines)"),this);
    mediumSize->setCheckable(true);
    connect(mediumSize,SIGNAL(triggered()),this,SLOT(mediumBoard()));

    largeSize = new QAction(tr("Large board (30x16 spaces, 99 mines)"),this);
    largeSize->setCheckable(true);
    connect(largeSize,SIGNAL(triggered()),this,SLOT(largeBoard()));

    boardSize = new QActionGroup(this);
    boardSize->addAction(smallSize);
    boardSize->addAction(mediumSize);
    boardSize->addAction(largeSize);
    smallSize->setChecked(true);

}

void MainWindow::createMenus()
{
    //Add menues
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);

    //Add submenue for board size
    sizeMenu = fileMenu->addMenu(tr("Board size"));
    sizeMenu->addAction(smallSize);
    sizeMenu->addAction(mediumSize);
    sizeMenu->addAction(largeSize);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    //Add help menu with "about"-box
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::setup(int x, int y, int mines)
{
    int size_x, size_y;
    board = new GameBoard(x,y,mines,&size_x,&size_y);
    connect(board,SIGNAL(gameStarts()),this,SLOT(start()));
    connect(board,SIGNAL(moves(int)),this,SLOT(moves(int)));
    view = new QGraphicsView(board);
    setCentralWidget(view);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(Qt::lightGray);
    QString message = tr("Take a guess!");
    statusBar()->showMessage(message);
    size_x += 20;
    size_y += 70;
    setMinimumSize(size_x, size_y);
    resize(size_x, size_y);
}
