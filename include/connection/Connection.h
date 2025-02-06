//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include "logger.h"
#include <string>
#include <iostream>
#include "json.hpp"

typedef nlohmann::json json;
typedef asio::ip::tcp::resolver resolver;
typedef websocket::stream<tcp::socket> socket;

class Connection {
  private:
    const std::string url;
    const std::string port;
    const std::string host;

    Logger logger;

    resolver c_resolver;
    socket c_socket;

  public:
  Connection(boost::asio::io_context& ctx, const std::string &host_,
               const std::string &port_, const std::string &url_);

    void connect();
    bool isConnected();
    void close();

    void send(const json &message);
    std::string recieve();
}

#endif //CONNECTION_H
