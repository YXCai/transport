#include "transport.h"

using boost::asio::ip::udp;

int main()
{
    try{
        boost::asio::io_service io_service;
        udp_transport testTransport(io_service);
        std::cout << "Enter 1 for recv socket, 2 for send socket" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            testTransport.bind();
            testTransport.recv();
        }
        else 
        {
            testTransport.send_connect();
            testTransport.send();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
