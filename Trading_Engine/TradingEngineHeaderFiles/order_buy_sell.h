//
// Created by Abigail Sorenson on 6/24/24.
//

#ifndef ORDER_BUY_SELL_H
#define ORDER_BUY_SELL_H

#include <sstream>
using std::ostringstream;

#include<string>
using std::string;

#include "transactions.h"
#include "order_type.h"
#include "order_stat.h"
#include "order.h"
#include "order_limit.h"
#include "order_tree.h"

class Order_buy_sell {

private:
    Order_tree tree_buy;
    Order_tree tree_sell;
    ostringstream data_output;
    int orders_total_submitted;

public:
    Order_buy_sell() : tree_buy(Order_type::BUY), tree_sell(Order_type::SELL), orders_total_submitted(0) {};

    // getting funcs
    Order_tree& getTreeBuy();
    Order_tree& getTreeSell();
    Order_tree& getOrderTreeByType(const Order_type& order_type);
    const int& getTotalOrdersSubmitted() ;
    const int& getTotalOrdersFull() ;
    const int& getTotalOrdersUnFull() ;
    string getResults();
    void getSnapshot();

    //other funcs
    void orderProcess(Order& order_incoming); //executes order or stores it if not filled
    void orderCancel(const std::shared_ptr<Order>&  order_cancel);






};

#endif //ORDER_BUY_SELL_H
