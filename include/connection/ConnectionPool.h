//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

typedef boost::asio::io_context asio_ctx;

class ConnectionPool {
    private:
        const size_t n_connections;

        std::mutex p_mutex;
        std::vector<std::shared_ptr<Connection>> pool;

        Logger logger;
        asio_ctx ctx;

        Connection buildConnection();

        const std::string host;
        const std::string port;
        const std::string url;

    public:
        ConnectionPool(size_t n_connections, std::string &host, std::string &port, std::string &url);
        std::shared_ptr<Connection> acquire();
        bool isEmpty();
        void release(std::shared_ptr<Connection> conn);
};


#endif //CONNECTIONPOOL_H
