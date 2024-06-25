//
// Created by Abigail Sorenson on 6/24/24.
// manages order limit with balanced binary tree based on price no time element
//

#ifndef ORDER_TREE_H
#define ORDER_TREE_H

#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

#include "order.h"
#include "order_limit.h"
#include "order_stat.h"
#include "order_type.h"
#include "transactions.h"

class Order_tree {

public:
    std::unordered_set<unsigned int> order_set; /* Unordered set with unique orders */
    std::map<float, int> order_tree; /* Map (red-black tree) with LimitOrder price as key and LimitOrder length as value */
    std::unordered_map<float, Order_limit> map_price; /* Unordered map with LimitOrder price as key and LimitOrder as value */
    Order_type type;
    float price_max;
    float price_min;

public:
    Order_tree() : order_set({}), order_tree({}), map_price({}), price_min(std::numeric_limits<float>::quiet_NaN()), price_max(std::numeric_limits<float>::quiet_NaN()), type(type_tree) {};

    //getting funcs
    size_t getLen() const;
    const float& getPriceMin();
    const float& getPriceMax();
    const Order_type& getType() const;

    //setting funcs
    void setPriceMin(const float& min_new);
    void setPriceMax(const float& max_new);

    //other funcs
    void addOrderPrice(Order& order_incoming);
    void deleteOrderPrice(const std::shared_ptr<Order>& order_delete);
    void deletePriceLimit(const float& price_limit);
    void matchPriceOrder(Order& order_incoming, std::ostringstream& store_transac);

};




#endif //ORDER_TREE_H
