#ifndef ORDER_H
#define ORDER_H

enum class Side {
    BUY,
    SELL
};

struct Order {
    long id;
    Side side;
    double price;
    double quantity;
    long timestamp;
};

#endif // ORDER_H