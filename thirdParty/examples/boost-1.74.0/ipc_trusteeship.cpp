#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "boost/bind.hpp"
#include <iostream>

void test1()
{
    boost::interprocess::shared_memory_object::remove("Highscore");
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
    int *i = managed_shm.construct<int>("Integer")(99);
    std::cout << *i << std::endl;
    std::pair<int *, std::size_t> p = managed_shm.find<int>("Integer");
    if (p.first)
        std::cout << *p.first << std::endl;
}

void test2()
{
    boost::interprocess::shared_memory_object::remove("Highscore");
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
    int *i = managed_shm.construct<int>("Integer")[10](99);
    std::cout << *i << std::endl;
    // managed_shm.destroy<int>("Integer");
    std::pair<int *, std::size_t> p = managed_shm.find<int>("Integer");
    if (p.first)
    {
        std::cout << *p.first << std::endl;
        std::cout << p.second << std::endl;
    }
}

void test3()
{
    boost::interprocess::shared_memory_object::remove("Highscore");
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> string;
    string *s = managed_shm.find_or_construct<string>("String")("Hello!", managed_shm.get_segment_manager());
    s->insert(5, ", world");
    std::cout << *s << std::endl;
}

// void construct_objects(boost::interprocess::managed_shared_memory &managed_shm)
// {
//     managed_shm.construct<int>("Integer")(99);
//     managed_shm.construct<float>("Float")(3.14);
// }

// void test4()
// {
//     boost::interprocess::shared_memory_object::remove("Highscore");
//     boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
//     managed_shm.atomic_func(boost::bind(construct_objects, boost::ref(managed_shm)));
//     std::cout << *managed_shm.find<int>("Integer").first << std::endl;
//     std::cout << *managed_shm.find<float>("Float").first << std::endl;
// }

int main(int argc, char const *argv[])
{
    test3();

    return 0;
}
