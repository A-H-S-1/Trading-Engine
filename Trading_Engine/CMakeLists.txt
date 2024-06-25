cmake_minimum_required(VERSION 3.28)
project(Trading_Engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Trading_Engine main.cpp
        TradingEngineHeaderFiles/transactions.h
        TradingEngineHeaderFiles/order.h
        TradingEngineHeaderFiles/order_type.h
        TradingEngineHeaderFiles/order_stat.h
        TradingEngineHeaderFiles/order_limit.h
        TradingEngineHeaderFiles/order_tree.h
        TradingEngineHeaderFiles/order_buy_sell.h
        src/transactions.cpp
        src/order_type.cpp
        src/order_stat.cpp
        src/order_tree.cpp
        src/order_limit.cpp
        src/order.cpp
        src/order_buy_sell.cpp
        src/ST.cpp
        src/MT.cpp)
