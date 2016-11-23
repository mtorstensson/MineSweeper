#include "counter.h"

Counter::Counter(int initial_amount, int n_number, int x, int y, bool use_sign)
    :digits(n_number), sign(use_sign), amount(initial_amount)
{
    max_amount =1;
    for(int i=0; i<digits;i++)
        max_amount *= 10;
    setPos(x,y);
    //setPlainText(QString::number(amount));
}

void Counter::increase(int n)
{
    amount += n;
    if(amount >= max_amount)
    {
        amount = max_amount;
        emit(maxed());
    }
}

void Counter::decrease(int n)
{
    amount -= n;
    if(sign && amount <= -max_amount)
    {
        amount = -max_amount;
        emit(minimized());
    }
    if(!sign && amount <= 0)
    {
        amount = 0;
        emit(minimized());
    }
}

void Counter::set(int n)
{
    amount = n;
}


