//
// Created by Abigail Sorenson on 6/24/24.
// Declaration for Order, Order_stat, Order_type classes
// Order class handles incoming orders (data structure)
// Order_stat and Order_type are properties of Order
// Orders are stored as doubly linked lisy
//

#ifndef ORDER_H
#define ORDER_H

#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>
#include "order_stat.h"
#include "order_type.h"

class Order {

    std::string sym;
    unsigned int id;
    float price;
    float quantity_original;
    float quanitity_current_remaining;
    float quanitity_current_transaction;
    float quanitity_total_transacted;
    std::shared_ptr<Order> order_next;
    std::shared_ptr<Order> order_prev;

    Order_type type;
    Order_stat status;

    Order(std::string symbol_input, unsigned int id_input, Order_type type_input, float quantity_original_input, float price_input);

    //setting funcs
    void setQuantityCurrentRemaining(const float& quantity_input);
    void setQuantityCurrentTransaction(const float& quantity_input);
    void setQuantityTotalTransacted(const float& quantity_input);
    void setOrderStatus(const Order_stat& status_new);

    //getting funcs
    const float& getPrice() const;
    const float& getQuantityCurrentRemaining() const;
    const float& getQuantityCurrentTransaction() const;
    const float& getQuantityTotalTransacted() const;
    const float& getQuantityOriginal() const;
    const std::string& getSymbol();
    const Order_type& getType() const;
    const Order_stat& getStatus() const;
    const unsigned int& getID() const;

    //other funcs

    // matches partial/complete orders and returns true for complete trade and false for partial trade
    bool MatchCompleteOrPartial(Order& order_incoming);

    //executes the order from MatchCompleteOrPartial then updates order quantities
    void TransactionExecute(const float& quantity_transaction_input);

    //order information storage
    void storeOrderInformation(const std::string& col_input, std::ostringstream& data_output);
};

#endif //ORDER_H
