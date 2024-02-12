#include "socket_client.hpp"

int main(int argc, char* argv[]) {
    int rc = -1;

    switch (argc)
    {
    case 2:
        {
            if (strlen(argv[1]) > 0) {
                int cmd = atoi(argv[1]);

                if (cmd >= 1 && cmd <= 8) {
                    boost::asio::io_service io_service;
                    Client client(io_service);

                    client.connect();
                    client.send(argv[1]);
                    io_service.run();
                    rc = 0;
                }
            }
        }
        break;
    default:
        rc = 1;
        break;
    }
    if (rc != 0) {
        std::cerr << "Usage: client <command> [1-8]" << std::endl;
    }
    return rc;
}
