#include "counter.h"

Counter::Counter(int initial_amount, int n_number, int x, int y, bool use_sign)
    :amount(initial_amount), digits(n_number), sign(use_sign)
{
    max_amount =1;
    for(int i=0; i<digits;i++)
        max_amount *= 10;
    setPos(x,y);
    font = new QFont("Purisa");
    font->setPixelSize(40);
    setFont(*font);
    if(amount < 0)
        setDefaultTextColor(Qt::red);
    else
        setDefaultTextColor(Qt::green);

    setPlainText(QString::number(amount));
    ensureVisible();
}

void Counter::increase(int n)
{
    amount += n;
    if(amount >= max_amount)
    {
        amount = max_amount;
        emit(maxed());
    }
    changed();
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
    changed();
}

void Counter::set(int n)
{
    amount = n;
    changed();
}

void Counter::change(bool add)
{
    if(add)
        increase();
    else
        decrease();
    changed();
}

void Counter::changed()
{
    if(amount < 0)
        setDefaultTextColor(Qt::red);
    else
        setDefaultTextColor(Qt::green);
    setPlainText(QString::number(amount));
    update();
}


