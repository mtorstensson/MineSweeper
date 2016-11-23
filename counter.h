#ifndef COUNTER_H
#define COUNTER_H

#include <QGraphicsItem>
#include <QObject>

class Counter : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Counter(int initial_amount=0, int n_number=2,int x=0, int y=0, bool use_sign =true);

signals:
    void maxed();
    void minimized();
    
public slots:
    void increase(int n=1);
    void decrease(int n=1);
    void set(int n);

private:
    int amount;
    int max_amount;
    int digits;
    bool sign;
};

#endif // COUNTER_H
