#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/sync/named_mutex.hpp"
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "boost/thread.hpp"
#include <iostream>

void test1()
{
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx");
    named_mtx.lock();
    ++(*i);
    std::cout << *i << std::endl;
    named_mtx.unlock();
}

void test2()
{
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::interprocess_mutex *mtx = managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")();
    mtx->lock();
    ++(*i);
    std::cout << *i << std::endl;
    mtx->unlock();
    // managed_shm.destroy<int>("Integer");
}

void test3()
{
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")(0);
    boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx");
    boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd");
    boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);
    while (*i < 10)
    {
        if (*i % 2 == 0)
        {
            ++(*i);
            named_cnd.notify_all();
            named_cnd.wait(lock);
        }
        else
        {
            std::cout << *i << std::endl;
            ++(*i);
            named_cnd.notify_all();
            named_cnd.wait(lock);
        }
    }
    named_cnd.notify_all();
    boost::interprocess::shared_memory_object::remove("shm");
    boost::interprocess::named_mutex::remove("mtx");
    boost::interprocess::named_condition::remove("cnd");
}

void test4()
{
    try
    {
        boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
        int *i = managed_shm.find_or_construct<int>("Integer")(0);
        boost::interprocess::interprocess_mutex *mtx = managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")();
        boost::interprocess::interprocess_condition *cnd = managed_shm.find_or_construct<boost::interprocess::interprocess_condition>("cnd")();
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*mtx);
        while (*i < 10)
        {
            if (*i % 2 == 0)
            {
                ++(*i);
                cnd->notify_all();
                cnd->wait(lock);
            }
            else
            {
                std::cout << *i << std::endl;
                ++(*i);
                cnd->notify_all();
                cnd->wait(lock);
            }
        }
        cnd->notify_all();
    }
    catch (...)
    {
        std::cout << "exception" << std::endl;
    }
    boost::interprocess::shared_memory_object::remove("shm");
}

int main(int argc, char const *argv[])
{
    test4();
    
    return 0;
}
