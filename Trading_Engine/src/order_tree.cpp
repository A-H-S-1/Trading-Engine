//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "../TradingEngineHeaderFiles/order_tree.h"

#include "../TradingEngineHeaderFiles/order_type.h"
#include "../TradingEngineHeaderFiles/order_stat.h"
#include "../TradingEngineHeaderFiles/order_limit.h"
#include "../TradingEngineHeaderFiles/order.h"
#include "../TradingEngineHeaderFiles/transactions.h"

#include <cmath>;
#include <memory>
using std::shared_ptr;

#include <sstream>
using std::ostringstream;

size_t Order_tree::getLen() const {
    return order_set.size();
}

const float& Order_tree::getPriceMax() {
    return price_max;
}

const float& Order_tree::getPriceMin() {
    return price_max;
}

void Order_tree::setPriceMax(const float& max_new) {
    price_max = max_new;
}

void Order_tree::setPriceMin(const float& min_new) {
    price_min = min_new;
}

const Order_type& Order_tree::getType() const {
    return type;
}

void Order_tree::deletePriceLimit(const float& price_limit) {
    map_price.erase(price_limit);
    order_tree.erase(price_limit);

    if (price_max == price_limit) {

        if (order_tree.empty()) {
            price_max = std::numeric_limits<float>::quiet_NaN();
        }
        else {
            price_max = order_tree.rbegin()->first;
        }
    }

    if (price_min == price_limit) {

        if (order_tree.empty()) {
            price_min = std::numeric_limits<float>::quiet_NaN();
        }
        else {
            price_min = order_tree.rbegin()->first;
        }
    }
}

void Order_tree::addOrderPrice(Order& order_incoming) {
    order_tree[order_incoming.getPrice()]++;
    map_price[order_incoming.getPrice()].addOrder(order_incoming);
    order_set.insert(order_incoming.getID());

    if (std::isnan(price_min) || price_min > order_incoming.getPrice()) {
        price_min = order_incoming.getPrice();
    }

    if (std::isnan(price_max) || price_max < order_incoming.getPrice()) {
        price_max = order_incoming.getPrice();
    }
}

void Order_tree::deleteOrderPrice(const std::shared_ptr<Order>& order_delete) {
    if (order_set.erase(order_delete->getID()) == 0) {
        return;
    }

    map_price[order_delete->getPrice()].deleteOrder(order_delete);

    if (map_price[order_delete->getID()].getLen() <= 0) {
        map_price.erase(order_delete->getPrice());
    }

    order_tree[order_delete->getPrice()]--;

    if (order_tree[order_delete->getPrice()] <= 0) {
        order_tree.erase(order_delete->getPrice());
    }

    if (price_max == order_delete->getPrice()) {

        if (order_tree.empty()) {
            price_max = std::numeric_limits<float>::quiet_NaN();
        }

        else if (map_price.find(order_delete->getPrice()) == map_price.end()) {
            price_max = order_tree.rbegin()->first;
        }
    }

    if (price_min == order_delete->getPrice()) {

        if (order_tree.empty()) {
            price_min = std::numeric_limits<float>::quiet_NaN();
        }

        else if (map_price.find(order_delete->getPrice()) == map_price.end()) {
            price_min = order_tree.begin()->first;
        }
    }
}

void Order_tree::matchPriceOrder(Order& order_incoming, std::ostringstream& store_transac) {

    if (map_price.empty()) {
        return;
    }

    if (order_incoming.getType() == type) {
        return;
    }

    auto match_price = (order_incoming.getType() == Order_type::BUY) ? getPriceMin() : getPriceMax();
    auto& order_Quantity_curr_remaining = order_incoming.getQuantityCurrentRemaining();
    auto& order_Price = order_incoming.getPrice();
    auto& order_Type = order_incoming.getType();

    /* Only match Buy and Sell orders where Sell price < Buy price */
    while (order_Quantity_curr_remaining > 0 &&
        ((order_Type == Order_type::SELL && order_Price <= match_price) ||
            (order_Type == Order_type::BUY && order_Price >= match_price))) {

        /* We access the appropriate LimitOrderand then start matching */
        Order_limit& match_limit_order = map_price[match_price];
        match_limit_order.matchOrders(order_incoming, order_set, store_transac);

        /* Delete LimitOrder if its empty */
        if (match_limit_order.getLen() == 0) {
            deletePriceLimit(match_price);
            /* If there are no Order's left to match with the incoming Order, we exit the loop */
            if (map_price.size() == 0) {
                break;
            }
            /* Otherwise we go to the next best price to match */
            match_price = (order_incoming.getType() == Order_type::BUY) ? getPriceMin() : getPriceMax();
        }
            }
    return;
}
