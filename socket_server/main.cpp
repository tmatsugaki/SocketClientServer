#include <cstdio>
#include "socket_server.hpp"

#if (USE_IO_SERVICE_RUN == true)
int main()
{
    std::string socket_name = "/tmp/unix_socket";
    std::remove(socket_name.c_str());
    boost::asio::io_service io_service;
    Server server(socket_name, io_service);

    server.start();
    server.process();
}
#else
#include <chrono>
#include <cinttypes>
#include <cstdint>
#include <cstdlib>
//#include <iostream>
#include <vector>

#define BOOST_COROUTINES_NO_DEPRECATION_WARNING
//#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

extern "C" {
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
}

using namespace std::chrono_literals;
using boost::asio::local::stream_protocol;

auto main(int argc, char** argv) -> int {
    boost::asio::io_context ctx{};
    boost::asio::local::stream_protocol::acceptor acceptor(ctx, stream_protocol::endpoint("/tmp/unix_socket"));
    boost::asio::local::stream_protocol::socket socket(ctx);
    boost::asio::io_context::strand strand{ctx};
    boost::asio::steady_timer timer{ctx};
/*
    boost::asio::spawn(strand, [](auto&& yield) {
        for (;;) {
        }
    });
    ctx.run();
*/
}
#endif