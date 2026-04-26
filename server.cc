#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

int main() {
    io_context io;

    // Server socket banao
    // tcp::acceptor = tera listening socket
    tcp::acceptor acceptor(io, 
        tcp::endpoint(tcp::v4(), 9001));

    std::cout << "Server ready port 9001" << std::endl;

    // Client socket banao — accept ke liye
    tcp::socket socket(io);

    // Ek client ka wait karo — blocking
    acceptor.accept(socket);
    std::cout << "Client aaya!" << std::endl;

    return 0;
}
