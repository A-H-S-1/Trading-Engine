//
// Created by Abigail Sorenson on 6/24/24.
// declaration for Order type map and Order_type enum
//order type map is used to hold string representation of Order
//

#ifndef ORDER_TYPE_H
#define ORDER_TYPE_H

#include <string>
#include <unordered_map>

enum class Order_type {
    SELL,
    BUY,
    CANCEL
};

extern std::unordered_map<Order_type, std::string> order_map_type;


#endif //ORDER_TYPE_H
