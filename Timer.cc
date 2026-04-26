#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::chrono;

int main() {
    io_context io;

    steady_timer t1(io, seconds(2));
    steady_timer t2(io, seconds(1));

    t1.async_wait([](boost::system::error_code ec){
        std::cout << "T1 — 2 sec" << std::endl;
    });

    t2.async_wait([](boost::system::error_code ec){
        std::cout << "T2 — 1 sec" << std::endl;
    });

    io.run();
    return 0;
}
