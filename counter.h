#ifndef COUNTER_H
#define COUNTER_H

#include <QGraphicsItem>
#include <QObject>
#include <QFont>

class Counter : public QGraphicsTextItem
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
    void change(bool add);

private:
    void changed();
    int amount;
    int max_amount;
    int digits;
    bool sign;
    QFont* font;
};

#endif // COUNTER_H
