#include <iostream>
#include <string>
#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include "boost/array.hpp"

namespace socket_asio
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::socket sock(io_service);
    boost::array<char, 4096> buffer;

    void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            std::cout << "333333333" << std::endl;
            std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;
            sock.async_read_some(boost::asio::buffer(buffer), read_handler);
        }
    }

    void connect_handler(const boost::system::error_code &ec)
    {
        if (!ec)
        {
            std::cout << "22222" << std::endl;
            boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
            sock.async_read_some(boost::asio::buffer(buffer), read_handler);
        }
    }

    void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it)
    {
        if (!ec)
        {
            std::cout << "11111" << std::endl;
            sock.async_connect(*it, connect_handler);
        }
    }

    void test_h1()
    {
        // 域名解析器
        boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80");
        resolver.async_resolve(query, resolve_handler);
        io_service.run();
    }
} // namespace socket_asio

void test_hpp()
{
    socket_asio::test_h1();
}