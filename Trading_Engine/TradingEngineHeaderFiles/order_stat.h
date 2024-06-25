//
// Created by Abigail Sorenson on 6/24/24.
// decleration for order status map and Order_stat enum
//

#ifndef ORDER_STAT_H
#define ORDER_STAT_H

#include <string>
#include <unordered_map>

enum class Order_stat {
    ORDER_NEW,
    FILl_COMPLETE,
    FILL_PARTIAL,
    STORED
};

extern std::unordered_map<Order_stat, std::string> order_map_status;

#endif //ORDER_STAT_H
