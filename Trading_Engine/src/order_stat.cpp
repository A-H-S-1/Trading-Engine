//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "../TradingEngineHeaderFiles/order_stat.h"

#include <string>
using std::string;

#include<unordered_map>
using std::unordered_map;

unordered_map<Order_stat, string> order_status_map = {
    {Order_stat::ORDER_NEW,"ORDER NEW"},
    {Order_stat::FILL_PARTIAL,"FILL PARTIAL"},
    {Order_stat::FILl_COMPLETE,"FILL COMPLETE"},
    {Order_stat::STORED,"STORED"}
};
