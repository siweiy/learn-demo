/*
    共享内存
*/

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

void test1()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write);
    shdmem.truncate(1024);
    std::cout << shdmem.get_name() << std::endl;
    boost::interprocess::offset_t size;
    if (shdmem.get_size(size))
    {
        std::cout << size << std::endl;
    }
}

void test2()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write);
    shdmem.truncate(1024);
    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
    std::cout << std::hex << "0x" << region.get_address() << std::endl;
    std::cout << std::dec << region.get_size() << std::endl;
    boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only);
    std::cout << std::hex << "0x" << region2.get_address() << std::endl;
    std::cout << std::dec << region2.get_size() << std::endl;
}

void test3()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write);
    shdmem.truncate(1024);
    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
    char *i1 = static_cast<char *>(region.get_address());
    strcpy(i1, "123124jkdjvskdlvjsdkljgskdlgjskldgjsdklgjsl");
    boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only);
    char *i2 = static_cast<char *>(region2.get_address());
    std::cout << i2 << std::endl;

    // 如果 remove() 没有被调用, 那么，即使进程终止，共享内存还会一直存在
    bool removed = boost::interprocess::shared_memory_object::remove("Highscore");
    std::cout << removed << std::endl;
}

int main()
{
    test3();

    return 0;
}
