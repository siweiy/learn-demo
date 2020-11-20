/*
    Boost.Asio 异步输入输出
*/

#include "asio_test.hpp"

namespace Test
{

    void handler1(const boost::system::error_code &ec)
    {
        std::cout << "2 s." << std::endl;
    }

    void handler2(const boost::system::error_code &ec)
    {
        std::cout << "4 s." << std::endl;
    }

    void test1()
    {
        boost::asio::io_service io_service;
        boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(2)); //计时器
        timer.async_wait(handler1);                                                   // 立刻返回
        // async_wait() 会启动一个异步操作并立即返回，而 run() 则是阻塞的
        std::cout << "11111" << std::endl;
        io_service.run(); // 必须调用
        std::cout << "2222" << std::endl;
    }

    void test2()
    {
        boost::asio::io_service io_service;
        boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(2));
        timer1.async_wait(handler1);
        boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(4));
        timer2.async_wait(handler2);
        io_service.run();
    }

    //*********************************
    boost::asio::io_service io_service;

    void run()
    {
        io_service.run();
    }

    void test3()
    {
        boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(2));
        timer1.async_wait(handler1);
        boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(2));
        timer2.async_wait(handler2);
        boost::thread thread1(run);
        boost::thread thread2(run);
        thread1.join();
        thread2.join();
    }

    //*************************************
    boost::asio::io_service io_service1;
    boost::asio::io_service io_service2;

    void run1()
    {
        io_service1.run();
    }

    void run2()
    {
        io_service2.run();
    }

    void test4()
    {
        boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(2));
        timer1.async_wait(handler1);
        boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(2));
        timer2.async_wait(handler2);
        boost::thread thread1(run1);
        boost::thread thread2(run2);
        thread1.join();
        thread2.join();
    }
} // namespace Test

int main(int argc, char const *argv[])
{
    test_hpp();

    return 0;
}
