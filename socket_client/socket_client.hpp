#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <spdlog/fmt/ostr.h>

class Client {

public:
    Client(boost::asio::io_service& io_service);
    ~Client();
    void connect();
    void send(char *command);

private:
    void on_send(const boost::system::error_code& error, boost::shared_ptr<std::string> data);
    void on_receive(const boost::system::error_code& error, boost::shared_ptr<boost::asio::streambuf> data);

    boost::asio::io_service& io_service_;
    boost::asio::local::stream_protocol::socket socket_;
    short command;
};
