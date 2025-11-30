#include "OrderBook.h"
#include <iostream>

void OrderBook::add_order(const Order& order) {
    if (order.side == Side::BUY) {
        bids.push_back(order);
        // todo: don't use '&' and check perf loss, make order bigger, check perf difference between reference and copy
        sort(bids.begin(), bids.end(), [](const Order& a, const Order& b) {
            return a.price > b.price; // todo: dont sort on every pushback
        });
    } else if (order.side == Side::SELL) {
        asks.push_back(order);
        sort(asks.begin(), asks.end(), [](const Order& a, const Order& b) {
            return a.price < b.price; // todo: dont sort on every pushback
        });
    }
    // todo: add logic for matching orders
}

const std::vector<Trade>& OrderBook::get_recent_trades() const {
    return trades;
}