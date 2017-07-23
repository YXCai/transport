#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <boost/array.hpp>
#include "abs_transport.h"
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ref.hpp>

using boost::asio::ip::udp;

class udp_transport
{
    public:
        udp_transport(boost::asio::io_service& io_service);
        virtual void send();
        virtual void recv();
        void bind();
        void send_connect();

    private:
        boost::asio::io_service& io_service;
        boost::shared_ptr<udp::socket> socket_;
        udp::endpoint receiver_endpoint;
        udp::endpoint sender_endpoint;
        boost::array<char, 1024> send_buf;
        boost::array<char, 1024> recv_buf;
        udp::resolver resolver;
};
#endif
