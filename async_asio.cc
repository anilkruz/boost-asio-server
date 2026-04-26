#include <iostream>
#include <boost/asio.hpp>
#include <memory>

using namespace boost::asio;
using namespace boost::asio::ip;
using boost::system::error_code;
//10k clients test karne se pehle — persistent connection chahiye.
void handle_client(std::shared_ptr<tcp::socket> socket) {
    auto buf = std::make_shared<std::array<char, 1024>>();

    socket->async_read_some(buffer(*buf),
        [socket, buf](error_code ec, size_t bytes) {
            if(ec) {
                std::cout << "Client gaya\n";
                return;
            }

            std::string msg(buf->data(), bytes);
            auto response = std::make_shared<std::string>(
                "Echo: " + msg);

            async_write(*socket, buffer(*response),
                [socket, response](error_code ec, size_t) {
                    if(!ec) {
                        // dobara padho — recursive ✅
                        handle_client(socket);
                    }
                });
        });
}
/*// ek client handle karne ka function
void handle_client(std::shared_ptr<tcp::socket> socket) {
    // heap pe buffer banao
    auto buf = std::make_shared<std::array<char, 1024>>();

    // async read — non-blocking
    socket->async_read_some(buffer(*buf),
        [socket, buf](error_code ec, size_t bytes) {
            if(ec) {
                std::cout << "Client gaya\n";
                return;
            }

            std::string msg(buf->data(), bytes);
            std::cout << "Mila: " << msg << std::endl;

            // async write — wapas bhejo
            auto response = std::make_shared<std::string>(
                "Server ne suna: " + msg);

            async_write(*socket, buffer(*response),
                [socket, response](error_code ec, size_t) {
                    if(!ec) {
                        std::cout << "Bheja!\n";
                    }
                });
        });
}*/

int main() {
    io_context io;

    tcp::acceptor acceptor(io,
        tcp::endpoint(tcp::v4(), 9001));

    std::cout << "Server ready — port 9001\n";

    // accept function — recursive
    std::function<void()> do_accept;
    do_accept = [&]() {
        auto socket = std::make_shared<tcp::socket>(io);

        acceptor.async_accept(*socket,
            [&, socket](error_code ec) {
                if(!ec) {
                    std::cout << "Client aaya!\n";
                    handle_client(socket);
                }
                // agla client ka wait
                do_accept();
            });
    };
    do_accept();  // pehla accept shuru karo
    io.run();     // event loop

    return 0;
}
