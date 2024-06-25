//
// Created by Abigail Sorenson on 6/24/24.
// declaration of composition class responsible for managing objects of Order class with doubly linked lists
// added and removed using FIFO
// New orders are added to end
// matching orders is done at front only
//

#ifndef ORDER_LIMIT_H
#define ORDER_LIMIT_H

#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

#include "transactions.h"
#include "order.h"
#include "order_stat.h"
#include "order_type.h"

class Order_limit {
    std::shared_ptr<Order> order_limit_last;
    std::shared_ptr<Order> order_limit_first;
    int order_limit_len;

public:
    Order_limit() : order_limit_last(nullptr), order_limit_first(nullptr), order_limit_len(0) {};

//getting functions
    const std::shared_ptr<Order>& getFirst();
    const std::shared_ptr<Order>& getLast();
    int getLen() const;

//setting and updating funcs
    int updateLen(const int& update_num);
    void setFirst(const std::shared_ptr<Order>& order_incoming);
    void setLast(const std::shared_ptr<Order>& order_incoming);
    void addOrder(Order& order_incoming); //adds order to tail
    void deleteOrder(const std::shared_ptr<Order>& order_delete); // removes order from list
    //matches orders at front of list, removes order and appends order details to orders_executed
    void matchOrders(Order& order_incoming, std::unordered_set<unsigned int>& order_set, std::ostringstream& orders_executed);

};

#endif //ORDER_LIMIT_H
