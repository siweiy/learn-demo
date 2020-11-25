#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

void test1()
{
    boost::gregorian::date d(2010, 1, 30);
    std::cout << d.year() << std::endl;
    std::cout << d.month() << std::endl;
    std::cout << d.day() << std::endl;
    std::cout << d.day_of_week() << std::endl;
    std::cout << d.end_of_month() << std::endl;
}

void test2()
{
    boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
    std::cout << d.year() << std::endl;
    std::cout << d.month() << std::endl;
    std::cout << d.day() << std::endl;

    d = boost::gregorian::date_from_iso_string("20100131");
    std::cout << d.year() << std::endl;
    std::cout << d.month() << std::endl;
    std::cout << d.day() << std::endl;
}

void test3()
{
    boost::gregorian::date d1(2008, 1, 31);
    boost::gregorian::date d2(2020, 8, 31);
    boost::gregorian::date_duration dd = d2 - d1;
    std::cout << dd.days() << std::endl;
}

void test4()
{
    boost::gregorian::date_duration dd(4);
    std::cout << dd.days() << std::endl;
    boost::gregorian::weeks ws(4);
    std::cout << ws.days() << std::endl;
    boost::gregorian::months ms(4);
    std::cout << ms.number_of_months() << std::endl;
    boost::gregorian::years ys(4);
    std::cout << ys.number_of_years() << std::endl;
}

void test5()
{
    // std::locale::global(std::locale("German"));
    std::string months[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
    std::string weekdays[7] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
    boost::gregorian::date d(2009, 1, 7);
    boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%A, %d. %B %Y");
    df->long_month_names(std::vector<std::string>(months, months + 12));
    df->long_weekday_names(std::vector<std::string>(weekdays, weekdays + 7));
    std::cout.imbue(std::locale(std::cout.getloc(), df));
    std::cout << d << std::endl;
}

int main(int argc, char const *argv[])
{
    test5();

    return 0;
}
