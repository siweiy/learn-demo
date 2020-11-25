/*
    字符串操作
*/

#include <iostream>
#include <locale>
#include <clocale>
#include <cstring>
#include <vector>
#include "boost/algorithm/string.hpp"
#include "boost/algorithm/string/regex.hpp"

// 全局区域设置可以使用类 std::locale 中的静态函数 global() 改变
void test1() {
    std::locale loc;
    std::cout << loc.name() << std::endl; 

    std::cout << std::strcoll("ä", "z") << std::endl; // 73, 字符串比较 == strcmp
    std::locale::global(std::locale("en_US.UTF-8")); 
    std::cout << std::strcoll("ä", "z") << std::endl; // -25

    std::cout << loc.name() << std::endl;
}

//  Boost.StringAlgorithms
void test2() {

    std::setlocale(LC_ALL, "en_US.UTF-8"); 
    std::string s = "Boris Schäling"; 

    // 不改变源数据
    std::cout << boost::algorithm::to_upper_copy(s) << std::endl; // BORIS SCHäLING
    std::cout << boost::algorithm::to_lower_copy(s, std::locale("C")) << std::endl; // boris schäling

    // 改变源数据
    std::cout << s << std::endl; // Boris Schäling
    boost::algorithm::to_upper(s);
    std::cout << s << std::endl; // BORIS SCHäLING
    boost::algorithm::to_lower(s, std::locale("C"));
    std::cout << s << std::endl; // boris schäling

}

void test3() {

    std::locale::global(std::locale("en_US.UTF-8")); 
    std::string s = "Boris Schiling 0 "; 

    // 去除copy修改源数据
    std::cout << "erase_first_copy-->" << boost::algorithm::erase_first_copy(s, "i") << std::endl; 
    std::cout << "erase_nth_copy-->" << boost::algorithm::erase_nth_copy(s, "i", 0) << std::endl; 
    std::cout << "erase_last_copy-->" << boost::algorithm::erase_last_copy(s, "i") << std::endl; 
    std::cout << "erase_all_copy-->" << boost::algorithm::erase_all_copy(s, "i") << std::endl; 
    std::cout << "erase_head_copy-->" << boost::algorithm::erase_head_copy(s, 5) << std::endl; 
    std::cout << "erase_tail_copy-->" << boost::algorithm::erase_tail_copy(s, 8) << std::endl; 
}

void test4() {

    std::string s = "Boris Schäling"; 
    boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "Boris"); 
    std::cout << r << std::endl; 
    r = boost::algorithm::find_first(s, "xyz"); 
    std::cout << r << std::endl;
}

void test5() {
    std::vector<std::string> v; 
    v.push_back("Boris"); 
    v.push_back("Schäling");
    v.push_back("test"); 
    std::cout << boost::algorithm::join(v, " ") << std::endl;
    std::cout << boost::algorithm::join(v, "++") << std::endl;
}

void test6() {
    
    std::string s = "Boris Schäling"; 
    std::cout << boost::algorithm::replace_first_copy(s, "B", "D") << std::endl; 
    std::cout << boost::algorithm::replace_nth_copy(s, "B", 0, "D") << std::endl; 
    std::cout << boost::algorithm::replace_last_copy(s, "B", "D") << std::endl; 
    std::cout << boost::algorithm::replace_all_copy(s, "B", "D") << std::endl; 
    std::cout << boost::algorithm::replace_head_copy(s, 5, "Doris") << std::endl; 
    std::cout << boost::algorithm::replace_tail_copy(s, 8, "Becker") << std::endl; 
}

void test7() {

    // std::string s = "\t Boris Schäling \t"; 
    // std::cout << "." << boost::algorithm::trim_left_copy(s) << "." << std::endl; 
    // std::cout << "." << boost::algorithm::trim_right_copy(s) << "." << std::endl; 
    // std::cout << "." << boost::algorithm::trim_copy(s) << "." << std::endl;

    std::string s = "--Boris Schäling--"; 
    std::cout << "." << boost::algorithm::trim_left_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl; 
    std::cout << "." << boost::algorithm::trim_right_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl; 
    std::cout << "." << boost::algorithm::trim_copy_if(s, boost::algorithm::is_any_of("-")) << "." << std::endl;

    std::string str = "123456789Boris Schäling123456789"; 
    std::cout << "." << boost::algorithm::trim_left_copy_if(str, boost::algorithm::is_digit()) << "." << std::endl; 
    std::cout << "." << boost::algorithm::trim_right_copy_if(str, boost::algorithm::is_digit()) << "." << std::endl; 
    std::cout << "." << boost::algorithm::trim_copy_if(str, boost::algorithm::is_digit()) << "." << std::endl;
}

void test8() {

    std::string s = "Boris Schäling"; 
    std::cout << boost::algorithm::starts_with(s, "Boris") << std::endl; 
    std::cout << boost::algorithm::ends_with(s, "Schäling") << std::endl; 
    std::cout << boost::algorithm::contains(s, "is") << std::endl; 
    std::cout << boost::algorithm::lexicographical_compare(s, "Boris") << std::endl; // 0表示字串存在与s
}

void test9() {
    std::string s = "Boris Schäling"; 
    std::vector<std::string> v; 
    boost::algorithm::split(v, s, boost::algorithm::is_space()); // 以空格为裁剪依据，得到《Boris》《Schäling》
    std::cout << v.size() << std::endl; 
}

void test10() {

    std::string s = "Boris Schäling"; 
    boost::iterator_range<std::string::iterator> r = boost::algorithm::find_regex(s, boost::regex("\\w\\s\\w")); 
    std::cout << r << std::endl; 
}

int main(int argc, char const *argv[])
{
    test10();

    return 0;
}
