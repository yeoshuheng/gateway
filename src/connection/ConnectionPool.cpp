//
// Created by Yeo Shu Heng on 6/2/25.
//
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

#include "logger.h"
#include "ConnectionPool.h"
#include "Connection.h"

ConnectionPool::ConnectionPool(size_t n_connections_,
                               std::string &host_,
                               std::string &port_,
                               std::string &url_) {
  n_connections = n_connections_;
  host = host_;
  port = port_;
  url = url_;
  logger.log(INFO, std::format("[ConnectionPool] Constructing connection pool with %d connections...", n_connections));
  pool.reserve(n_connections);
  for (size_T i = 0; i < n_connections; i++) {
    pool.push_back(std::make_shared<Connection>(buildConnection()));
  }
  logger.log(INFO, std::format("[ConnectionPool] Constructed connection pool with %d connections", n_connections));
}

bool ConnectionPool::isEmpty() {
  return pool.empty();
}

std::shared_ptr<Connection> ConnectionPool::acquire() {
  std::lock_guard<std::mutex> lock(p_mutex); // releases lock once end of function scope
  if (!isEmpty()) {
    auto conn = pool.back();
    pool.pop_back();
    return conn;
  }
  return nullptr;
};

void ConnectionPool::release(std::shared_ptr<Connection> conn) {
  std::lock_guard<std::mutex> lock(p_mutex);
  pool.push_back(conn);
}

Connection ConnectionPool::buildConnection() {
  return Connection(ctx, host, port, url);
}
