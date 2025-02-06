//
// Created by Yeo Shu Heng on 6/2/25.
//
#include <thread>
#include <memory>
#include <chrono>
#include <random>

#include "Command.h"
#include "Connection.h"

int Command::getQuantum() {
  return dist(gen);
}

void Command::execute() {
    while (true) {
      std::shared_ptr<Connection> conn = pool.acquire();
      if (conn) {
        conn->send(order);
        pool.release(conn);
        return; // acquired connection & release connection
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(getQuantum()));
      }
    }
}
