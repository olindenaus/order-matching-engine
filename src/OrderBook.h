#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include "Order.h"
#include "Trade.h"

class OrderBook {
public:
    void add_order(const Order& order);
    void remove_order(long order_id);
    const std::vector<Trade>& get_recent_trades() const;
    const std::vector<Order>& get_bids() const { return bids; }
    const std::vector<Order>& get_asks() const { return asks; }

private:
    std::vector<Order> bids;
    std::vector<Order> asks;
    std::vector<Trade> trades;
};
#endif // ORDERBOOK_H