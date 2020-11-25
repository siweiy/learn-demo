/*
    词汇分割器库 Boost.Tokenizer
*/

#include <iostream>
#include <string>
#include "boost/tokenizer.hpp"

void test1() {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
    std::string s = "Boost C++ libraries1.";
    // tokenizer tok(s);

    // boost::char_separator<char> sep(" "); 
    // tokenizer tok(s, sep); // 以sep(" ")设定的符号分割

    boost::char_separator<char> sep(" ", "+"); 
    tokenizer tok(s, sep); // 以sep(" ", "+")设定的符号分割,第二个参数指定了需要显示的分隔符
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void test2() {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
    std::string s = "Boost C++ libraries"; 
    // 如果连续找到两个分隔符，他们之间的部分表达式将为空。
    // 在默认情况下，这些空表达式是不会显示的。第三个参数可以改变默认的行为
    boost::char_separator<char> sep(" ", "+", boost::keep_empty_tokens); 
    tokenizer tok(s, sep); 
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void test3() {
    typedef boost::tokenizer<boost::char_separator<wchar_t>, std::wstring::const_iterator, std::wstring> tokenizer; 
    std::wstring s = L"Boost C++ libraries"; 
    boost::char_separator<wchar_t> sep(L" "); 
    tokenizer tok(s, sep); 
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
        std::wcout << *it << std::endl;
    } 
}

void test4() {
    // boost::escaped_list_separator 类用于读取由逗号分隔的多个值
    // 它甚至还可以处理双引号以及转义序列
    typedef boost::tokenizer<boost::escaped_list_separator<char> > tokenizer; 
    std::string s = "Boost,\"C++ libraries\""; 
    tokenizer tok(s); 
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void test5() {
    typedef boost::tokenizer<boost::offset_separator> tokenizer; 
    //                   5    5        9
    std::string s = "Boost C++ libraries"; 
    // boost::offset_separator 指定了部分表达式应当在字符串中的哪个位置结束
    int offsets[] = { 5, 5, 9 }; 
    boost::offset_separator sep(offsets, offsets + 3); 
    tokenizer tok(s, sep); 
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    test5();

    return 0;
}
