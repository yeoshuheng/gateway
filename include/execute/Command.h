//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <random>
#include "ConnectionPool.h"

class Command {
    private:
      const std::string order;

      ConnectionPool pool; // pool cannot be const because we acquire & release -> modifications

      // Decide on quantum: how long to wait if we don't get a active connection.
      const std::random_device rd;
      const std::mt19937 gen(rd());
      const std::uniform_int_distribution<> dist(50, 200);
      int getQuantum();

    public:
      Command(const std::string &order, ConnectionPool &pool);
      void execute();
};


#endif //COMMAND_H
