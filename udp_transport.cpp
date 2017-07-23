#include "transport.h"

using boost::asio::ip::udp;

udp_transport::udp_transport(boost::asio::io_service& io_service)
    : io_service(io_service), resolver(io_service)
{
    socket_ = boost::make_shared<udp::socket>(boost::ref(io_service));
    send_buf = {{'g'}};
}

void udp_transport::send_connect()
{
    socket_ = boost::make_shared<udp::socket>(boost::ref(io_service), udp::endpoint(udp::v4(), 13));
    boost::system::error_code error; 
    socket_->receive_from(boost::asio::buffer(recv_buf), receiver_endpoint, 0, error);

    if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);
}
void udp_transport::send()
{
    socket_->send_to(boost::asio::buffer(send_buf), receiver_endpoint); 
}

void udp_transport::recv()
{
    size_t len = socket_->receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
    std::cout.write(recv_buf.data(), len);
}

void udp_transport::bind()
{
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), "127.0.0.1", "daytime");
    receiver_endpoint = *resolver.resolve(query);
    socket_ = boost::make_shared<udp::socket>(boost::ref(io_service));
    socket_->open(udp::v4());
    socket_->send_to(boost::asio::buffer(recv_buf), receiver_endpoint);
    
}
