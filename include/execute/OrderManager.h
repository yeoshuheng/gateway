//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <string>
#include <vector>
#include <iostream>

#include "Order.h"
#include "ConnectionPool.h"

class OrderManager {
    private:
      Order buildOrder();
      ConnectionPool conn_pool;
      Logger logger;

      bool validateOrder();

    public:
      OrderManager() {
        size_t n_connections = std::getenv("GATEWAY_N_CONN");
        std::string host = std::getenv("GATEWAY_HOST");
        std::string port = std::getenv("GATEWAY_PORT");
        std::string url = std::getenv("GATEWAY_URL");

        logger.log(LogLevel::INFO, "Setting up OrderManager");
        logger.log(LogLevel::INFO, "Host: %s Port: %s URL: %s", host, port, url);

        conn_pool = ConnectionPool(n_connections, host, port, url);

      };
      void handleOrder();
};

#endif //ORDERMANAGER_H
