#include "gameboard.h"

GameBoard::GameBoard(int x, int y, int n_mines)
  :x_max(x), y_max(y), mines(n_mines)
{
    return;
}

GameBoard::GameBoard(int x, int y, int n_mines, int *size_x, int *size_y)
  :x_max(x), y_max(y), mines(n_mines)
{
    srand(time(NULL));
    state = true;
    setSceneRect(0, 0, IMG_X*x_max, IMG_Y*y_max+100);
    *size_x = IMG_X*x_max;
    *size_y = IMG_Y*y_max+100;
    first = true;

    //TODO: Är NoIndex rätt i detta läget?
    setItemIndexMethod(QGraphicsScene::NoIndex);


    dummy = new Space(-IMG_X,-IMG_Y);
    empty = x_max*y_max - mines;
    if(empty <= 0)
        return;
    for(x=0; x<x_max; x++)
    {
        for(y=0; y<y_max; y++)
        {
            spaces[x_max*y+x] = new Space(IMG_X*x,IMG_Y*y+100);
            connect(spaces[x_max*y+x],SIGNAL(kaboom()),this,SLOT(hit_mine()));
            connect(spaces[x_max*y+x],SIGNAL(clicked(Space*)),this,SLOT(move_made(Space*)));
            connect(this,SIGNAL(kaboom()),spaces[x_max*y+x],SLOT(explode()));
            addItem(spaces[x_max*y+x]);
        }
    }
//    Counter(int initial_amount=0, int n_number=2,int x=0, int y=0, bool use_sign =true);
//    timeCounter = new Counter(0, 3, 0, 0,false);
//    mineCounter = new Counter(mines, 2, 500,0,true);
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
    char tmp[] = "Game over!\n\n\n";
//	if(spaces)
//		delete [] spaces;
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
    emit kaboom();
}

void GameBoard::move_made(Space *clicked)
{
    if(first)
    {
        // Placera ut minor
        setup(clicked);
        // Starta timer
//        connect(timer,SIGNAL(timeout()),timeCounter,SLOT(increase()));
//        timer->start(1000); // Timer räknar sekunder
        //Nolla moves
        moves_made = 1;
        first = false;
    }
    else
        moves_made++;
}

/*
Space* GameBoard::nb(int x, int y)
{
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
    return nb;
}
*/

