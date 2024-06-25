//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "..\TradingEngineHeaderFiles/order_limit.h"

#include "../TradingEngineHeaderFiles/order_type.h"
#include "../TradingEngineHeaderFiles/order_stat.h"
#include "../TradingEngineHeaderFiles/order.h"
#include "../TradingEngineHeaderFiles/transactions.h"

#include <unordered_set>
using std::unordered_set;

#include <memory>
using std::shared_ptr;

#include <sstream>
using std::ostringstream;

int Order_limit::getLen() const{
    return order_limit_len;
}

const std::shared_ptr<Order>& Order_limit::getFirst() {
    return order_limit_first;
}

const std::shared_ptr<Order>& Order_limit::getLast() {
    return order_limit_last;
}

int Order_limit::updateLen(const int& update_num) {
    order_limit_len += update_num;
}

void Order_limit::setFirst(const std::shared_ptr<Order>& order_incoming) {
    order_limit_first = order_incoming;
}

void Order_limit::setLast(const std::shared_ptr<Order>& order_incoming) {
    order_limit_len = order_incoming;
}

void Order_limit::addOrder(Order& order_incoming) {
    const std::shared_ptr<Order>& incoming_order_ptr = std::make_shared<Order>(order_incoming);

    order_limit_len++;

    if (order_limit_len == 1) {
        order_limit_first = incoming_order_ptr;
        order_limit_last = incoming_order_ptr;
    }

    else {
        incoming_order_ptr->prev_order = order_limit_last;
        order_limit_last->next_order = incoming_order_ptr;
        order_limit_last = incoming_order_ptr;
    }
}

void Order_limit::deleteOrder(const std::shared_ptr<Order>& order_delete) {
    order_limit_len--;

    if (order_limit_len - 1 <= 0) {
        order_limit_first = nullptr;
        order_limit_last = nullptr;
        return;
    }

    const shared_ptr<Order>& nxt_order = order_delete->next_order;
    const shared_ptr<Order>& prv_order = order_delete->prev_order;

    if (nxt_order != nullptr && prv_order != nullptr) {
        nxt_order->prev_order = prv_order;
        prv_order->next_order = nxt_order;
    }

    else if (nxt_order != nullptr) {
        nxt_order->prev_order = nullptr;
        order_limit_first = nxt_order;
    }

    else if (prv_order != nullptr) {
        prv_order->next_order = nullptr;
        order_limit_last = prv_order;
    }

}

void Order_limit::matchOrders(Order& order_incoming, std::unordered_set<unsigned int>& order_set, std::ostringstream& orders_executed) {
    /* The first Order in the LinkedList to start matching with */
    shared_ptr<Order> current_linked_list_order = order_limit_first;

    /* We will match the incoming_order with Order's in our LinkedList until the incoming_order
    is complete or the LinkedList is empty. The first if condition indicates that the incoming_order
    is partially filled and the else condition indicates that the incoming_order is completely filled. */
    while (order_incoming.getPeakQuantity() > 0 && order_limit_len > 0) {

        bool match = current_linked_list_order->Match(order_incoming);

        /* Complete trade, meaning the current LinkedList order is fully completed. */
        if (match) {
            /* Next order within the LinkedList. */
            shared_ptr<Order> next_current_linked_list_order = current_linked_list_order->next_order;

            /* Store fulfilled order */
            current_linked_list_order->storeOrderInfo(orders_executed, "\033[32m");

            /* Delete LinkedList order from order set */
            order_set.erase(current_linked_list_order->getID());
            /* Delete order from LinkedList. */
            deleteOrder(current_linked_list_order);
            /* Release the memory as order is no longer in use */
            current_linked_list_order.reset();

            /* Next order in LinkedList. */
            current_linked_list_order = next_current_linked_list_order;
        }
    }
    return;
}
