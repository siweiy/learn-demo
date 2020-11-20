/*
    正则表达式

普通字符:
    runoo+b，可以匹配 runoob、runooob、runoooooob 等    + 号代表前面的字符必须至少出现一次（1次或多次）。
    runoo*b，可以匹配 runob、runoob、runoooooob 等      * 号代表前面的字符可以不出现，也可以出现一次或者多次（0次、或1次、或多次）。
    colou?r 可以匹配 color 或者 colour                 ? 问号代表前面的字符最多只可以出现一次（0次、或1次）。
    [aeiou] 匹配字符串                                 匹配 aeiou 所有字符
    [^aeiou] 匹配字符串                                除了 e o u a 字母的所有字母
    [A-Z] 表示一个区间，                                匹配所有大写字母
    [a-z] 表示一个区间，                                表示所有小写字母。
    .                                                匹配除换行符（\n、\r）之外的任何单个字符，相等于 [^\n\r]
    [\s\S]	                                         匹配所有。\s 是匹配所有空白符，包括换行，\S 非空白符，包括换行。
    \w	                                             匹配字母、数字、下划线。等价于 [A-Za-z0-9_]

非打印字符:
    \cx	匹配由x指明的控制字符。例如， \cM 匹配一个 Control-M 或回车符。x 的值必须为 A-Z 或 a-z 之一。否则，将 c 视为一个原义的 'c' 字符。
    \f	匹配一个换页符。等价于 \x0c 和 \cL。
    \n	匹配一个换行符。等价于 \x0a 和 \cJ。
    \r	匹配一个回车符。等价于 \x0d 和 \cM。
    \s	匹配任何空白字符，包括空格、制表符、换页符等等。等价于 [ \f\n\r\t\v]。注意 Unicode 正则表达式会匹配全角空格符。
    \S	匹配任何非空白字符。等价于 [^ \f\n\r\t\v]。
    \t	匹配一个制表符。等价于 \x09 和 \cI。
    \v	匹配一个垂直制表符。等价于 \x0b 和 \cK。

特殊字符:
    $	匹配输入字符串的结尾位置。如果设置了 RegExp 对象的 Multiline 属性，则 $ 也匹配 '\n' 或 '\r'。要匹配 $ 字符本身，请使用 \$。
    ( )	标记一个子表达式的开始和结束位置。子表达式可以获取供以后使用。要匹配这些字符，请使用 \( 和 \)。
    *	匹配前面的子表达式零次或多次。要匹配 * 字符，请使用 \*。
    +	匹配前面的子表达式一次或多次。要匹配 + 字符，请使用 \+。
    .	匹配除换行符 \n 之外的任何单字符。要匹配 . ，请使用 \. 。
    [	标记一个中括号表达式的开始。要匹配 [，请使用 \[。
    ？	匹配前面的子表达式零次或一次，或指明一个非贪婪限定符。要匹配 ? 字符，请使用 \?。
    \	将下一个字符标记为或特殊字符、或原义字符、或向后引用、或八进制转义符。例如， 'n' 匹配字符 'n'。'\n' 匹配换行符。序列 '\\' 匹配 "\"，而 '\(' 则匹配 "("。
    ^	匹配输入字符串的开始位置，除非在方括号表达式中使用，当该符号在方括号表达式中使用时，表示不接受该方括号表达式中的字符集合。要匹配 ^ 字符本身，请使用 \^。
    {	标记限定符表达式的开始。要匹配 {，请使用 \{。
    |	指明两项之间的一个选择。要匹配 |，请使用 \|。

限定符:
    *	匹配前面的子表达式零次或多次。例如，zo* 能匹配 "z" 以及 "zoo"。* 等价于{0,}。
    +	匹配前面的子表达式一次或多次。例如，'zo+' 能匹配 "zo" 以及 "zoo"，但不能匹配 "z"。+ 等价于 {1,}。
    ？	匹配前面的子表达式零次或一次。例如，"do(es)?" 可以匹配 "do" 、 "does" 中的 "does" 、 "doxy" 中的 "do" 。? 等价于 {0,1}。
    {n}	n 是一个非负整数。匹配确定的 n 次。例如，'o{2}' 不能匹配 "Bob" 中的 'o'，但是能匹配 "food" 中的两个 o。
    {n,}	n 是一个非负整数。至少匹配n 次。例如，'o{2,}' 不能匹配 "Bob" 中的 'o'，但能匹配 "foooood" 中的所有 o。'o{1,}' 等价于 'o+'。'o{0,}' 则等价于 'o*'。
    {n,m}	m 和 n 均为非负整数，其中n <= m。最少匹配 n 次且最多匹配 m 次。例如，"o{1,3}" 将匹配 "fooooood" 中的前三个 o。'o{0,1}' 等价于 'o?'。请注意在逗号和两个数之间不能有空格。

例子：
    [0-9]{1,2} 或 [1-9][0-9]{0,1}  ==》  0～99
    <.*>   ==>   <h1>RUNOOB-菜鸟教程</h1>  ==> 表达式匹配从开始小于符号 (<) 到关闭 h1 标记的大于符号 (>) 之间的所有内容
*/

#include <iostream>
#include <boost/regex.hpp>
#include "boost/algorithm/string/regex.hpp"

// boost::algorithm::find_regex()
// boost::algorithm::replace_regex()
// boost::algorithm::erase_regex() 
// boost::algorithm::split_regex()

void test1() {

    std::string s = "Boris Schäling"; 
    boost::regex expr("Boris Schäling"); 
    std::cout << boost::regex_match(s, expr) << std::endl;// 全部匹配返回true，反之
}

void test2() {
    std::string s = "Boris Schäling"; 
    boost::regex expr("(\\w+)\\s(\\w+)"); 
    boost::smatch what;
    if (boost::regex_search(s, what, expr)) 
    { 
        std::cout << what[0] << std::endl; // Boris Sch
        std::cout << what[1] << "--" << what[2] << std::endl; 
    }
}

void test3() {
    std::string s = " Boris Schäling "; 
    boost::regex expr("\\s"); // 这里找到3个空白
    std::string fmt("==="); 
    std::cout << boost::regex_replace(s, expr, fmt) << std::endl; // 将得到的结果替换成fmt ： ===Boris===Schäling===
}

void test4() {
    std::string s = "Boris Schäling"; 
    boost::regex expr("(\\w+)\\s(\\w+)"); 
    std::string fmt("\\2 \\1"); 
    std::cout << boost::regex_replace(s, expr, fmt) << std::endl; // Sch Borisäling
}

void test5() {

    std::string s = "rtsp://admin:ematech1234@172.16.100.18/ipc"; 
    // 172.16.100.188
    boost::iterator_range<std::string::iterator> r = boost::algorithm::find_regex(s, boost::regex("((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}")); 
    std::cout << r << std::endl;
}

int main(int argc, char const *argv[])
{
    test5();
    
    return 0;
}
