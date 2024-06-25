//
// Created by Abigail Sorenson on 6/24/24.
// Decleration for Transac class which is responsible for storing executed orders (2 vectors, raw format and json format),
//

#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#pragma once

#include <vector>
#include <string>

class Transac {
    std::vector<std::string> orders_json;
    std::vector<std::string> orders_raw;

    public:
        Transactions() : orders_raw({}), orders_json({}) {};

        size_t getLen() const;

        size_t getNumOfExecOrders() const;

        void addOrder(const std::string& order_raw);
};

#endif //TRANSACTIONS_H
