#include<iostream>
#include<boost/asio.hpp>

int main(){
    
    boost::asio::io_context io;

    std::cout << "run() se pehle" << std::endl;
    io.run();  // koi kaam nahi diya
    std::cout << "run() ke baad" << std::endl;
    return 0;
}
