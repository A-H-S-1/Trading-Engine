//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "..\TradingEngineHeaderFiles/transactions.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

size_t Transac::getNumOfExecOrders() const {
    return getLen()/2;
}

size_t Transac::getLen() const {
    return orders_raw.size();
}

void Transac::addOrder(const std::string& order_raw) {
    orders_raw.emplace_back(order_raw);
}
