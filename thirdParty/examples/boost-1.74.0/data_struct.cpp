#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <string>
#include <iostream>
#include <vector>

void test1()
{
    // typedef std::pair<std::string, std::string> person;
    // person p("Boris", "Schaeling");
    // std::cout << p.first.c_str() << p.second.c_str() << std::endl;

    typedef boost::tuple<std::string, std::string> person;
    person p("Boris", "Schaeling");
    std::cout << p << std::endl;
}

void test2()
{
    typedef boost::tuple<std::string, std::string, int> person;
    person p("Boris", "Schaeling", 43);
    std::cout << p << std::endl;

    std::cout << p.get<0>() << std::endl;
    boost::get<0>(p);
    p.get<1>() = "Becker";

    std::cout << boost::make_tuple("Boris", "Schaeling", 43) << std::endl;

    std::string s = "Boris";
    std::cout << boost::make_tuple(boost::ref(s), "Schaeling", 43) << std::endl;
}

void test3()
{
    // Tier 的特殊之处在于它包含的所有元素都是引用类型的
    typedef boost::tuple<std::string &, std::string &, int &> person;

    std::string firstname = "Boris";
    std::string surname = "Schaeling";
    int shoesize = 43;
    person p = boost::tie(firstname, surname, shoesize);
    // person p = boost::make_tuple(boost::ref(firstname), boost::ref(surname), boost::ref(shoesize));
    surname = "Becker";

    shoesize = 4;
    std::cout << p << std::endl;
}

void test4()
{
    boost::any a = 1;
    std::cout << boost::any_cast<int>(a) << std::endl;
    a = 3.14;
    std::cout << boost::any_cast<double>(a) << std::endl;
    a = true;
    std::cout << boost::any_cast<bool>(a) << std::endl;
    a = std::string("Hello, world!");
    std::cout << boost::any_cast<std::string>(a) << std::endl;
    if (!a.empty())
    {
        const std::type_info &ti = a.type();
        std::cout << ti.name() << std::endl;
    }
}

void test5()
{
    boost::variant<double, char, std::string> v;
    v = 3.14;
    std::cout << boost::get<double>(v) << std::endl;
    v = 'A';
    std::cout << boost::get<char>(v) << std::endl;
    v = "Hello, world!";
    std::cout << boost::get<std::string>(v) << std::endl;
    std::cout << v << std::endl;
}

std::vector<boost::any> vector;

struct output : public boost::static_visitor<>
{
    template <typename T>
    void operator()(T &t) const
    {
        vector.push_back(t);
    }
};

void test6()
{
    boost::variant<double, char, std::string> v;
    v = 3.14;
    boost::apply_visitor(output(), v);
    v = 'A';
    boost::apply_visitor(output(), v);
    v = "Hello, world!";
    boost::apply_visitor(output(), v);
}

int main(int argc, char const *argv[])
{
    test6();

    return 0;
}
