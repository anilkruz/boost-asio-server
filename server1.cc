#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

int main() {
    io_context io;

    tcp::acceptor acceptor(io,
        tcp::endpoint(tcp::v4(), 9001));

    std::cout << "Server ready port 9001" << std::endl;

    tcp::socket socket(io);
    acceptor.accept(socket);
    std::cout << "Client aaya!" << std::endl;

    // Client ka data padho
    char buf[1024]{};
    boost::system::error_code ec;

    // read_some = read() jaisa
    // "jo bhi data hai — padh lo"
    size_t bytes = socket.read_some(
        buffer(buf), ec);

    if(!ec) {
        std::cout << "Client ne bheja: " 
                  << buf << std::endl;

        // wapas bhejo
        write(socket, buffer("Server ne suna!\n"), ec);
    }

    return 0;
}
