#include <iostream>
#include "boost/filesystem.hpp"

void test1()
{
    boost::filesystem::path p("/home/ysw/nfs");
    // p /= "Windows";

    try
    {
        boost::filesystem::file_status s = boost::filesystem::status(p);
        std::cout << boost::filesystem::is_directory(s) << std::endl;

        std::cout << p.string() << std::endl;
        std::cout << p.filename() << std::endl;
        std::cout << p.root_path() << std::endl;
        std::cout << p.parent_path() << std::endl;
        std::cout << p.stem() << std::endl;
        std::cout << p.extension() << std::endl;
        // boost::filesystem::file_size(p);

        std::time_t t = boost::filesystem::last_write_time(p);
        std::cout << std::ctime(&t) << std::endl;

        boost::filesystem::space_info s2 = boost::filesystem::space(p);
        std::cout << s2.capacity << std::endl;
        std::cout << s2.free << std::endl;
        std::cout << s2.available << std::endl;

        std::string name = boost::filesystem::current_path().c_str();

        boost::filesystem::path p2(name + "/boost_test");
        std::cout << p2.c_str() << std::endl;
        if (boost::filesystem::create_directory(p2))
        {
            boost::filesystem::rename(p2, "boost_test1");
            boost::filesystem::remove("boost_test1");
        }else {
            std::cout << "create error" << std::endl;
        }
    }
    catch (boost::filesystem::filesystem_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void test2()
{
    boost::filesystem::path p("test.txt");
    boost::filesystem::ofstream ofs(p);
    ofs << "Hello, world!" << std::endl;
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}
