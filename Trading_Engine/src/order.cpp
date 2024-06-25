//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "../TradingEngineHeaderFiles/order.h"

#include "../TradingEngineHeaderFiles/order_type.h"
#include "../TradingEngineHeaderFiles/order_stat.h"

#include <string>
using std::string;
using std::to_string;

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::shared_ptr;

#include <algorithm>
using std::min;

#include <sstream>
using std::ostringstream;

Order::Order(std::string symbol_input, unsigned int id_input, Order_type type_input, float quantity_original_input, float price_input):
    sym(symbol_input), id(id_input), type(type_input), price(price_input), quantity_original(quantity_original_input) {

    status = Order_stat::ORDER_NEW;
    quanitity_current_remaining = quantity_original_input;
    quanitity_current_transaction = 0;
    quanitity_total_transacted = 0;
    order_next = nullptr;
    order_prev = nullptr;
}

const float& Order::getPrice() const {
    return price;
}

const Order_stat& Order::getStatus() const {
    return status;
}

const std::string& Order::getSymbol() {
    return sym;
}

const Order_type& Order::getType() const {
    return type;
}

const unsigned int& Order::getID() const {
    return id;
}

const float& Order::getQuantityOriginal() const {
    return quantity_original;
}

const float& Order::getQuantityCurrentRemaining() const {
    return quanitity_current_remaining;
}

const float& Order::getQuantityCurrentTransaction() const {
    return quanitity_current_transaction;
}

const float& Order::getQuantityTotalTransacted() const {
    return quanitity_total_transacted;
}

void Order::setOrderStatus(const Order_stat& status_new) {
    status = status_new;
}

void Order::setQuantityCurrentRemaining(const float& quantity_input) {
    quanitity_current_remaining += quantity_input;
}

void Order::setQuantityTotalTransacted(const float& quantity_input) {
    quanitity_total_transacted += quantity_input;
}

void Order::setQuantityCurrentTransaction(const float& quantity_input) {
    quanitity_current_transaction = quantity_input;
}

void Order::storeOrderInformation(const std::string& col_input, std::ostringstream& data_output) {
    data_output << col_input << "Order:- Symbol: " << sym << ", ID: " <<  id << ", Type: " <<
        order_map_type[type] << ", Price: " << price <<
        ", Orignal Quantity: " << quantity_original <<
        ", Quantity Left: " << quanitity_current_remaining <<
        ", Status: " << order_map_status[status] << "\033[0m" << std::endl;
}

void Order::TransactionExecute(const float& quantity_transaction_input) {
    setQuantityCurrentRemaining(-quantity_transaction_input);
    setQuantityCurrentTransaction(quantity_transaction_input);
    setQuantityTotalTransacted(quantity_transaction_input);
}

bool Order::MatchCompleteOrPartial(Order& order_incoming) {
    if (quanitity_current_remaining <= order_incoming.getQuantityCurrentRemaining()) {
        status = Order_stat::FILl_COMPLETE;
        if (quanitity_current_remaining == order_incoming.getQuantityCurrentRemaining()) {
            order_incoming.setOrderStatus(Order_stat::FILl_COMPLETE);
        }
        else {
            order_incoming.setOrderStatus(Order_stat::FILL_PARTIAL);
        }

        auto trans_quant = quanitity_current_remaining;
        this->TransactionExecute(trans_quant);
        order_incoming.TransactionExecute(trans_quant);

        return true;
    }
    else {
        status = Order_stat::FILL_PARTIAL;
        order_incoming.setOrderStatus(Order_stat::FILl_COMPLETE);

        auto trans_quant = order_incoming.quanitity_current_remaining;
        this->TransactionExecute(trans_quant);
        order_incoming.TransactionExecute(trans_quant);

        return false;
    }
}








