#include <iostream>
#include <iomanip>
#include "OrderBookPrinter.h"

void prettyPrintOrderBook(OrderBook ob)
{
    std::vector<Order> bids = ob.get_bids();
    std::vector<Order> asks = ob.get_asks();
    sort(asks.begin(), asks.end(), [](const Order &a, const Order &b)
         {
             return a.price < b.price; // todo: this is temporary for order book display purpose
         });

    sort(bids.begin(), bids.end(), [](const Order &a, const Order &b)
         {
             return a.price > b.price; // todo: this is temporary for order book display purpose
         });

    // Calculate column widths
    size_t sideWidth = 4; // "BUY" or "SELL"
    size_t idWidth = std::string("Order ID").length();
    size_t priceWidth = std::string("Price").length();
    size_t quantityWidth = std::string("Quantity").length();
    size_t timestampWidth = std::string("Timestamp").length();

    auto calculateWidths = [&](const std::vector<Order> &orders)
    {
        for (const Order &order : orders)
        {
            idWidth = std::max(idWidth, std::to_string(order.id).length());
            priceWidth = std::max(priceWidth, std::to_string(order.price).length());
            quantityWidth = std::max(quantityWidth, std::to_string(order.quantity).length());
            timestampWidth = std::max(timestampWidth, std::to_string(order.timestamp).length());
        }
    };

    calculateWidths(bids);
    calculateWidths(asks);

    // Print header
    std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;
    std::cout << "| " << std::setw(sideWidth) << "Side" << " | "
              << std::setw(idWidth) << "Order ID" << " | "
              << std::setw(priceWidth) << "Price" << " | "
              << std::setw(quantityWidth) << "Quantity" << " | "
              << std::setw(timestampWidth) << "Timestamp" << " |" << std::endl;
    std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;

    std::cout << "ASKS:\n";
    int displayLimit = 4;
    int displayed = 0;
    // fixme : displays only 4 WORST ASKS

    for(int i = std::min(static_cast<int>(asks.size()), displayLimit)-1; i >=0; --i)
    {
        Order ask = asks[i];
        std::cout << "| " << std::setw(sideWidth) << "SELL" << " | "
                  << std::setw(idWidth) << ask.id << " | "
                  << std::setw(priceWidth) << ask.price << " | "
                  << std::setw(quantityWidth) << ask.quantity << " | "
                  << std::setw(timestampWidth) << ask.timestamp << " |" << std::endl;
        if (displayed >= displayLimit)
            break;
    }

    displayed = 0;
    std::cout << "BIDS:\n";
    for (const Order &bid : bids)
    {
        std::cout << "| " << std::setw(sideWidth) << "BUY" << " | "
                  << std::setw(idWidth) << bid.id << " | "
                  << std::setw(priceWidth) << bid.price << " | "
                  << std::setw(quantityWidth) << bid.quantity << " | "
                  << std::setw(timestampWidth) << bid.timestamp << " |" << std::endl;
        if (++displayed >= displayLimit)
            break;
    }

    std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;
}

// void prettyPrintOrderBook(const std::vector<Order>& bids, const std::vector<Order>& asks) {
//     // Calculate column widths
//     size_t sideWidth = 4; // "BUY" or "SELL"
//     size_t idWidth = std::string("Order ID").length();
//     size_t priceWidth = std::string("Price").length();
//     size_t quantityWidth = std::string("Quantity").length();
//     size_t timestampWidth = std::string("Timestamp").length();

//     auto calculateWidths = [&](const std::vector<Order>& orders) {
//         for (const Order& order : orders) {
//             idWidth = std::max(idWidth, std::to_string(order.id).length());
//             priceWidth = std::max(priceWidth, std::to_string(order.price).length());
//             quantityWidth = std::max(quantityWidth, std::to_string(order.quantity).length());
//             timestampWidth = std::max(timestampWidth, std::to_string(order.timestamp).length());
//         }
//     };

//     calculateWidths(bids);
//     calculateWidths(asks);

//     // Print header
//     std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;
//     std::cout << "| " << std::setw(sideWidth) << "Side" << " | "
//               << std::setw(idWidth) << "Order ID" << " | "
//               << std::setw(priceWidth) << "Price" << " | "
//               << std::setw(quantityWidth) << "Quantity" << " | "
//               << std::setw(timestampWidth) << "Timestamp" << " |" << std::endl;
//     std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;

//     // Print bids
//     std::cout << "BIDS:\n";
//     for (const Order& bid : bids) {
//         std::cout << "| " << std::setw(sideWidth) << "BUY" << " | "
//                   << std::setw(idWidth) << bid.id << " | "
//                   << std::setw(priceWidth) << bid.price << " | "
//                   << std::setw(quantityWidth) << bid.quantity << " | "
//                   << std::setw(timestampWidth) << bid.timestamp << " |" << std::endl;
//     }

//     // Print asks
//     std::cout << "ASKS:\n";
//     for (const Order& ask : asks) {
//         std::cout << "| " << std::setw(sideWidth) << "SELL" << " | "
//                   << std::setw(idWidth) << ask.id << " | "
//                   << std::setw(priceWidth) << ask.price << " | "
//                   << std::setw(quantityWidth) << ask.quantity << " | "
//                   << std::setw(timestampWidth) << ask.timestamp << " |" << std::endl;
//     }

//     std::cout << "=" << std::string(sideWidth + idWidth + priceWidth + quantityWidth + timestampWidth + 20, '=') << "=" << std::endl;
// }