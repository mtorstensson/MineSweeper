#include "gameboard.h"

GameBoard::GameBoard(int x, int y, int n_mines)
  :QGraphicsScene(), x_max(x), y_max(y), mines(n_mines)
{
    return;
}

GameBoard::GameBoard(int x, int y, int n_mines, int *size_x, int *size_y)
  :QGraphicsScene(), x_max(x), y_max(y), mines(n_mines)
{
    srand(time(NULL));
    first = true;
    setSceneRect(0, 0, IMG_X*x_max, IMG_Y*y_max+100);
    *size_x = IMG_X*x_max;
    *size_y = IMG_Y*y_max+100;
    timer = new QTimer();

    //TODO: Is NoIndex the right index method for this?
    setItemIndexMethod(QGraphicsScene::NoIndex);


    dummy = new Space(-IMG_X,-IMG_Y);
    empty = x_max*y_max - mines;
    if(empty <= 0)
        return;
    statusIndicator = new Icon(100, 0);
    addItem(statusIndicator);
    connect(this,SIGNAL(gameEnd(bool)),statusIndicator,SLOT(gameEnd(bool)));
    connect(this,SIGNAL(restart()),statusIndicator,SLOT(reset()));
    connect(statusIndicator,SIGNAL(clicked()),this,SLOT(reset()));
    //    Counter(int initial_amount=0, int n_number=2,int x=0, int y=0, bool use_sign =true);
    timeCounter = new Counter(0, 3, 0, 0,false);
    addItem(timeCounter);
    mineCounter = new Counter(mines, 2, 200,0,true);
    addItem(mineCounter);
    for(x=0; x<x_max; x++)
    {
        for(y=0; y<y_max; y++)
        {
            spaces[x_max*y+x] = new Space(IMG_X*x,IMG_Y*y+100);
            connect(spaces[x_max*y+x],SIGNAL(kaboom()),this,SLOT(hit_mine()));
            connect(spaces[x_max*y+x],SIGNAL(clicked(Space*)),this,SLOT(move_made(Space*)));
            connect(spaces[x_max*y+x],SIGNAL(expanded()),this,SLOT(checkDone()));
            connect(spaces[x_max*y+x],SIGNAL(flagged(bool)),mineCounter,SLOT(change(bool)));
            connect(this,SIGNAL(gameEnd(bool)),spaces[x_max*y+x],SLOT(explode(bool)));
            connect(this,SIGNAL(restart()),spaces[x_max*y+x],SLOT(reset()));
            connect(statusIndicator,SIGNAL(clicked()),spaces[x_max*y+x],SLOT(reset()));
            addItem(spaces[x_max*y+x]);
        }
    }
}

void GameBoard::setup(Space *first)
{
    for(int i=0; i<mines; )
    {
        int mine = rand() % (x_max*y_max);
        if(!spaces[mine]->is_mine() && spaces[mine] != first)
        {
            spaces[mine]->is_mine(true);
            i++;
        }
    }

    for(int x=0; x<x_max; x++)
    {
        for(int y=0; y<y_max; y++)
        {
            //spaces[x_max*y+x]->setup(nb(x,y));
            Space *nb[8];
            if(y == 0)
            {
                nb[0] = dummy;
                nb[1] = dummy;
                nb[2] = spaces[(y  )*x_max+x+1];
                nb[3] = spaces[(y+1)*x_max+x+1];
                nb[4] = spaces[(y+1)*x_max+x  ];
                nb[5] = spaces[(y+1)*x_max+x-1];
                if(x == 0)
                    nb[6] = dummy;
                else
                    nb[6] = spaces[(y  )*x_max+x-1];
                nb[7] = dummy;

            }
            else if(y == y_max-1)
            {
                nb[0] = spaces[(y-1)*x_max+x  ];
                nb[1] = spaces[(y-1)*x_max+x+1];
                if(x == x_max-1)
                    nb[2] = dummy;
                else
                    nb[2] = spaces[(y  )*x_max+x+1];
                nb[3] = dummy;
                nb[4] = dummy;
                nb[5] = dummy;
                nb[6] = spaces[(y  )*x_max+x-1];
                nb[7] = spaces[(y-1)*x_max+x-1];
            }
            else
            {
                nb[0] = spaces[(y-1)*x_max+x  ];
                nb[1] = spaces[(y-1)*x_max+x+1];
                nb[2] = spaces[(y  )*x_max+x+1];
                nb[3] = spaces[(y+1)*x_max+x+1];
                nb[4] = spaces[(y+1)*x_max+x  ];
                nb[5] = spaces[(y+1)*x_max+x-1];
                nb[6] = spaces[(y  )*x_max+x-1];
                nb[7] = spaces[(y-1)*x_max+x-1];
            }
            if(x == 0)
            {
                nb[5] = dummy;
                nb[6] = dummy;
                nb[7] = dummy;
            }
            if(x == x_max-1)
            {
                nb[1] = dummy;
                nb[2] = dummy;
                nb[3] = dummy;
            }
            spaces[x_max*y+x]->setup(nb);
        }
    }

}


GameBoard::~GameBoard()
{

}

bool GameBoard::emptyLeft()
{
    empty = 0;
    for(int i=0; i< x_max*y_max; i++)
        if(spaces[i]->isLeft())
        {
            empty++;
        }
    if(empty > 0)
        return(true);
    else
        return(false);
}

void GameBoard::hit_mine()
{
    emit gameEnd(false);// Game did not end in victory
    timer->stop();
}

void GameBoard::move_made(Space *clicked)
{
    if(first)
    {
        emit gameStarts();
        // Place mines
        setup(clicked);
        // Start timer
        connect(timer,SIGNAL(timeout()),timeCounter,SLOT(increase()));
        timer->start(1000); // Timer counts seconds
        //Reset moves counter
        moves_made = 1;
        first = false;
    }
    else
        emit moves(++moves_made);
}

void GameBoard::checkDone()
{
    if(emptyLeft())
        return;
    timer->stop();
    emit gameEnd(true); // Game ended in victory!
    mineCounter->set(moves_made);

}

void GameBoard::reset()
{
    emit restart();
    timer->stop();
    mineCounter->set(mines);
    timeCounter->set(0);
    //statusIndicator->reset();
    first = true;

}

