//
// Created by Abigail Sorenson on 6/24/24.
//

#pragma once
#include "../TradingEngineHeaderFiles/order_type.h"

#include <string>
using std::string;

#include<unordered_map>
using std::unordered_map;

unordered_map<Order_type, string> order_type_map = {
    {Order_type::BUY, "BUY"},
    {Order_type::SELL, "SELL"},
    {Order_type::CANCEL, "CANCEL"}
};
