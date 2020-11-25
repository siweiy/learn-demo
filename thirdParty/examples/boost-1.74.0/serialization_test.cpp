#include <iostream>
#include <fstream>
#include <sstream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include <boost/serialization/string.hpp> 

std::stringstream ss;

#if 0
void save()
{
    // std::ofstream file("archiv.txt");
    // boost::archive::text_oarchive oa(file);
    boost::archive::text_oarchive oa(ss);
    int i = 1;
    oa << i;
}

void load()
{
    // std::ifstream file("archiv.txt");
    // boost::archive::text_iarchive ia(file);
    boost::archive::text_iarchive ia(ss);
    int i = 0;
    ia >> i;
    std::cout << i << std::endl;
}

#else
class person
{
public:
    person()
    {
    }

    person(int age)
        : age_(age)
    {
    }

    int age() const
    {
        return age_;
    }

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & age_;
    }

    int age_;
};

void save()
{
    boost::archive::text_oarchive oa(ss);
    person p(31);
    oa << p;
}

void load()
{
    boost::archive::text_iarchive ia(ss);
    person p;
    ia >> p;
    std::cout << p.age() << std::endl;
}

#endif

int main(int argc, char const *argv[])
{
    save();
    load();

    return 0;
}
