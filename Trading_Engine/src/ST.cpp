//
// Created by Abigail Sorenson on 6/25/24.
//
#include "../TradingEngineHeaderFiles/order_buy_sell.h"
#include "../TradingEngineHeaderFiles/order.h"
#include "../TradingEngineHeaderFiles/order_limit.h"
#include "../TradingEngineHeaderFiles/order_tree.h"
#include "../TradingEngineHeaderFiles/transactions.h"

#include <sstream>
#include <fstream>
#include <algorithm>

#include <random>
using std::uniform_real_distribution;
using std::mt19937;

#include <thread>
using std::thread;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

vector<Order> generateRandomOrders(int order_num, unsigned int seed) {
    unsigned int order_id = 0;

    mt19937 rng(seed);
    uniform_real_distribution<float> price_distribution(1.0f, 100.0f);
    uniform_real_distribution<float> qty_distribution(10.0f, 1000.0f);

    vector<Order> orders;
    orders.reserve(order_num);

    for (int i = 0; i < order_num; ++i) {
        order_id += 1;
        string order_symbol = (rng() % 2 == 0) ? "BTC" : "ETH";
        Order_type order_type = (rng() % 2 == 0) ? Order_type::BUY : Order_type::SELL;
        float order_price = price_distribution(rng);
        float order_qty = qty_distribution(rng);
        orders.emplace_back(Order(std::move(order_symbol), std::move(order_id),std::move(order_type), std::move(order_qty), std::move(order_price)));
    }

    return orders;
}

int main() {

    Order_buy_sell orderBookETH;
    Order_buy_sell orderBookBTC;

    auto orders = generateRandomOrders(100'000, 1);

    auto startTime = std::chrono::high_resolution_clock::now();

    for (auto& order : orders){
        /* Process the order through the order book */
        (order.getSymbol() == "BTC") ? orderBookBTC.orderProcess(std::ref(order)) : orderBookETH.orderProcess(std::ref(order));
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();

    cout << orderBookETH.getResults() + orderBookBTC.getResults() << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "A total of " << orderBookBTC.getTotalOrdersSubmitted() + orderBookETH.getTotalOrdersSubmitted() << " orders submitted " << endl;
    cout << "\033[33m" << "A total of " << orderBookBTC.getTotalOrdersUnFull() + orderBookETH.getTotalOrdersUnFull() << " orders still within OrderBook " << "\033[0m" << endl;
    cout << "\033[32m" << "A total of " << orderBookBTC.getTotalOrdersFull() + orderBookETH.getTotalOrdersFull() << " orders were fulfilled in " << elapsedTime << " seconds" << "\033[0m" << endl;
    return 0;
}
