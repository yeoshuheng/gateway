//
// Created by Yeo Shu Heng on 6/2/25.
//

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <string>
#include <iostream>

#include "Connection.h"
#include "Logger.h"

Connection::Connection(boost::asio::io_context& ctx,
                       const std::string &host_,
                       const std::string &port_,
                       const std::string &url_) {
    logger.log(INFO, "Resolving context...");
    c_resolver(ctx);
    c_socket(ctx);
    port = port_;
    host = host_;
    url = url_;

    connect();
}

bool isConnected() {
    return c_socket.next_layer().is_open();
}

void Connection::send(const std::string &message) {
    if (!isConnected()) {connect();}
    try {
      c_socket.write(asio::buffer(message));
      logger.log(INFO, std::format("[Connection] Sending message %s", message));
    } catch (const std::exception &e) {
      logger.log(ERROR, std::format("[Connection] Error Sending Message: %s | Error code: %s",
                                    e.what(), e.code()));
    }
}

std::string Connection::receive() {
  try {
    boost::beast::flat_buffer buffer;
    c_socket.read(buffer);
    std::string recv = boost::beast::buffers_to_string(buffer.data());

    logger.log(DEBUG, std::format("[Connection] Recieved: " + recv));

    return recv;

  } catch (const std::exception &e) {
    logger.log(INFO, std::format("[Connection] Error recieving message: %s | Error code: %s",
                                    e.what(), e.code()));
    return "";
  }
}

void Connection::close() {
  if (!isConnected()) {return;}
  try {
    logger.log(INFO, "[Connection] Closing connection...");
    c_socket.close(websocket::close_code::normal);
    logger.log(INFO, "[Connection] Connection closed");
  } catch (const std::exception &e) {
    logger.log(ERROR, std::format("[Connection] Error Sending Message: %s | Error code: %s",
                                    e.what(), e.code()));
  }
}

void Connection::connect() {
    logger.log(INFO, "Connecting...");
    std::string error_s;
    try {
        auto const results = c_resolver.resolve(host, port);
        asio::connect(c_socket.next_layer(),
                      results.begin(),
                      results.end());

        c_socket.handshake(host, url);
        logger.log(INFO, "Connected!");
    } catch (const asio::system_error &e) {
        error_s = std::format("[Connection] System error: %s | Error code: %d", e.what(), e.code());
        logger.log(ERROR, error_s);
    } catch (const asio::ssl::error &e) {
        error_s = std::format("[Connection] SSL error: %s | Error code: %d", e.what(), e.code());
        logger.log(ERROR, error_s);
    } catch (const std::exception &e) {
        error_s = std::format("[Connection] Unexpected exception: %s | Error code: %d", e.what(), e.code());
        logger.log(ERROR, error_s);
    }
}