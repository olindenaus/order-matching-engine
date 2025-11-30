#include <iostream>
#include <sstream>
#include <iomanip>
#include "OrderBook.h"
#include "main.h"
#include "OrderBookPrinter.h"
using namespace std;

void printCommands()
{
    cout << "======================== COMMANDS ========================\n";
    cout << "| sell <price> <quantity>  | Place a SELL order          |\n";
    cout << "| buy <price> <quantity>   | Place a BUY order           |\n";
    cout << "| trades                   | List recent trades          |\n";
    cout << "| orders                   | Show order book             |\n";
    cout << "| help                     | Pring available commands    |\n";
    cout << "| quit/exit/stop           | Kill the application        |\n";
    cout << "=========================================================\n";
}

void prettyPrintTrades(const std::vector<Trade> &trades)
{
    cout << "======================== RECENT TRADES ========================\n";
    cout << "| Trade ID | Buy Order ID | Sell Order ID | Price  | Quantity | Timestamp           |\n";
    cout << "================================================================\n";
    for (const Trade &trade : trades)
    {
        cout << "| " << trade.tradeId << "\t | "
             << trade.buyOrderId << "\t | "
             << trade.sellOrderId << "\t | "
             << trade.price << "\t | "
             << trade.quantity << "\t | "
             << trade.timestamp << "\t |\n";
    }
    cout << "================================================================\n";
}

istringstream readUserCmd()
{
    string userCommand;
    getline(cin, userCommand);

    istringstream commandStream(userCommand);
    return commandStream;
}

int main()
{
    static int orderIdCounter = 0;
    OrderBook ob = OrderBook();

    cout << "OrderBook created." << endl;
    printCommands();
    bool running = true;
    while (running)
    {
        istringstream commandStream = readUserCmd();
        string command;
        commandStream >> command;
        if (command == "sell" || command == "buy")
        {
            double price, quantity;
            if (!(commandStream >> price >> quantity))
            {
                cout << "Invalid command format." << endl;
                return 1;
            }
            Order order = Order();
            order.id = ++orderIdCounter;
            order.side = (command == "sell") ? Side::SELL : Side::BUY;
            order.price = price;
            order.quantity = quantity;
            order.timestamp = time(0);
            ob.add_order(order);
            cout << "Placed " << (command == "sell" ? "SELL" : "BUY") << " order: " << price << " " << quantity << endl;
            prettyPrintOrderBook(ob);
        }
        else if (command == "trades")
        {
            const vector<Trade> &trades = ob.get_recent_trades();
            prettyPrintTrades(trades);
        }
        else if (command == "orders")
        {
            prettyPrintOrderBook(ob);
        }
        else if (command == "help")
        {
            printCommands();
        }
        else if (command == "stop" || command == "exit")
        {
            running = false;
        }
        else
        {
            cout << "Unknown command." << endl;
        }
    }

    return 0;
}
