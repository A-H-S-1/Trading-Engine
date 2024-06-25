//
// Created by Abigail Sorenson on 6/24/24.
//

#include "../TradingEngineHeaderFiles/order_buy_sell.h"
#pragma once

#include "../TradingEngineHeaderFiles/order_type.h"
#include "../TradingEngineHeaderFiles/order_stat.h"
#include "../TradingEngineHeaderFiles/order.h"
#include "../TradingEngineHeaderFiles/order_limit.h"
#include "../TradingEngineHeaderFiles/order_tree.h"
#include "../TradingEngineHeaderFiles/transactions.h"

#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;
#include <memory>
using std::shared_ptr;
#include <fstream>
#include <cmath>
#include <algorithm>

string Order_buy_sell::getResults() {
    return data_output.str();
}

//fix!!!!
void Order_buy_sell::getSnapshot() {
    std::vector<std::pair<float, float>> sorted_buys(tree_buy.order_tree.begin(), tree_buy.order_tree.end());
    std::sort(sorted_buys.begin(), sorted_buys.end(), [](const auto& b1, const auto& b2) {
        return b1.first > b2.first;
        });

    for (size_t i = 1; i < sorted_buys.size(); ++i) {
        sorted_buys[i].second += sorted_buys[i - 1].second;
    }

    std::ofstream out_buy_prices("output_buy_prices.txt");

    for (const auto& buy : sorted_buys) {
        out_buy_prices << buy.first << ",";
    }
    out_buy_prices << std::endl;

    out_buy_prices.close();

    std::ofstream out_buy_sizes("output_buy_sizes.txt");

    for (const auto& buy : sorted_buys) {
        out_buy_sizes << buy.second << ",";
    }
    out_buy_sizes << std::endl;

    out_buy_sizes.close();

    std::vector<std::pair<float, float>> sorted_sells(tree_sell.order_tree.begin(), tree_sell.order_tree.end());
    std::sort(sorted_sells.begin(), sorted_sells.end(), [](const auto& b1, const auto& b2) {
        return b1.first < b2.first;
        });

    for (size_t i = 1; i < sorted_sells.size(); ++i) {
        sorted_sells[i].second += sorted_sells[i - 1].second;
    }

    std::ofstream out_sell_prices("output_sell_prices.txt");

    for (const auto& sell : sorted_sells) {
        out_sell_prices << sell.first << ",";
    }
    out_sell_prices << std::endl;

    out_sell_prices.close();

    std::ofstream out_sell_sizes("output_sell_sizes.txt");

    for (const auto& sell : sorted_sells) {
        out_sell_sizes << sell.second << ",";
    }
    out_sell_sizes << std::endl;

    out_sell_sizes.close();
}

Order_tree& Order_buy_sell::getTreeBuy() {
    return tree_buy;
}

Order_tree& Order_buy_sell::getTreeSell() {
    return tree_sell;
}

const int& Order_buy_sell::getTotalOrdersFull() {
    return orders_total_submitted - (tree_buy.getLen() + tree_sell.getLen());
}

const int& Order_buy_sell::getTotalOrdersSubmitted() {
    return orders_total_submitted;
}

const int& Order_buy_sell::getTotalOrdersUnFull() {
    return (tree_buy.getLen() + tree_sell.getLen());
}

Order_tree &Order_buy_sell::getOrderTreeByType(const Order_type &order_type) {
    return (order_type == Order_type::BUY) ? tree_buy : tree_sell;
}

void Order_buy_sell::orderCancel(const std::shared_ptr<Order>& order_cancel) {
    getOrderTreeByType(order_cancel->getType()).deleteOrderPrice(order_cancel);
}

void Order_buy_sell::orderProcess(Order& order_incoming) {
    orders_total_submitted++;

    order_incoming.storeOrderInformation("\033[0m", data_output);

    Order_tree& matching_tree = (order_incoming.getType() == Order_type::BUY) ? tree_sell : tree_buy;

    matching_tree.matchPriceOrder(order_incoming, data_output);

    if (order_incoming.getStatus() == Order_stat::FILl_COMPLETE) {

        order_incoming.storeOrderInformation( "\033[32m", data_output);
    }

    else {

        order_incoming.setOrderStatus(Order_stat::STORED);
        order_incoming.storeOrderInformation( "\033[33m", data_output);

        /* Place in appropriate Tree */
        Order_tree& storing_tree = (order_incoming.getType() == Order_type::BUY) ? tree_buy : tree_sell;
        storing_tree.addOrderPrice(order_incoming);

    }

    if (order_incoming.getID() == 75000) {
        getSnapshot();
    }

    return;
}



