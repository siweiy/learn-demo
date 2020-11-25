/*
    1、过滤器（Filter） - 过滤器在请求处理程序执行请求之前或之后，执行某些任务。
    
    @ 过滤器配合责任链模式，可以实现过滤器链。
    @ 过滤器链（Filter Chain） - 过滤器链带有多个过滤器，并在 Target 上按照定义的顺序执行这些过滤器。
*/

#include <iostream>
#include <string>
#include <list>
using namespace std;

class Person
{ //被过滤的对象的类型
private:
    string name;
    string gender;
    string work_num;

public:
    Person(string name, string gender, string work_num)
    {
        this->name = name;
        this->gender = gender;
        this->work_num = work_num;
    }
    string get_name() { return this->name; }
    string get_gender() { return this->gender; }
    string get_work_num() { return this->work_num; }
};

class Filter
{ //过滤器基类
public:
    virtual ~Filter() {}
    virtual list<Person> filter(list<Person> &persons) = 0;
    virtual Filter *clone() = 0;
};

class Name_Filter : public Filter
{ //名称过滤器
private:
    string name;

public:
    Name_Filter(string name) { this->name = name; }
    list<Person> filter(list<Person> &persons)
    {
        list<Person> result_persons;
        for (list<Person>::iterator it = persons.begin(); it != persons.end(); ++it)
        {
            if ((*it).get_name().find_first_of(name, 0) != -1)
            {
                result_persons.push_back(*it);
            }
        }
        return result_persons;
    }
    Name_Filter *clone()
    {
        Name_Filter *filter = new Name_Filter("");
        *filter = *this;
        return filter;
    }
};

class Gender_Filter : public Filter
{ //性别过滤器
private:
    string gender;

public:
    Gender_Filter(string gender) { this->gender = gender; }
    list<Person> filter(list<Person> &persons)
    {
        list<Person> result_persons;
        for (list<Person>::iterator it = persons.begin(); it != persons.end(); ++it)
        {
            if ((*it).get_gender() == this->gender)
            {
                result_persons.push_back(*it);
            }
        }
        return result_persons;
    }
    Gender_Filter *clone()
    {
        Gender_Filter *filter = new Gender_Filter("");
        *filter = *this;
        return filter;
    }
};

class WorkNum_Filter : public Filter
{ //工号过滤器
private:
    string work_num;

public:
    WorkNum_Filter(string work_num) { this->work_num = work_num; }
    list<Person> filter(list<Person> &persons)
    {
        list<Person> result_persons;
        for (list<Person>::iterator it = persons.begin(); it != persons.end(); ++it)
        {
            if ((*it).get_work_num().find_first_of(work_num, 0) != -1)
            {
                result_persons.push_back(*it);
            }
        }
        return result_persons;
    }
    WorkNum_Filter *clone()
    {
        WorkNum_Filter *filter = new WorkNum_Filter("");
        *filter = *this;
        return filter;
    }
};

class List_Filter : public Filter
{ //过滤管道
private:
    list<Filter *> filters;

public:
    List_Filter(list<Filter *> filters) { this->filters = filters; }
    ~List_Filter()
    {
        for (list<Filter *>::iterator filter = filters.begin(); filter != filters.end(); ++filter)
        {
            delete *filter;
            *filter = NULL;
        }
    }
    list<Person> filter(list<Person> &persons)
    {
        list<Person> result_persons = persons;
        for (list<Filter *>::iterator filter = filters.begin(); filter != filters.end(); ++filter)
        {
            result_persons = (*filter)->filter(result_persons);
        }
        return result_persons;
    }
    List_Filter *clone()
    {
        return NULL;
    }
};

void print_Persons(list<Person> persons)
{
    for (list<Person>::iterator person = persons.begin(); person != persons.end(); ++person)
    {
        cout << (*person).get_name() << " " << (*person).get_gender() << " " << (*person).get_work_num() << endl;
    }
}

int main(int argc, const char *argv[])
{
    list<Person> persons;
    persons.push_back(Person("a", "男", "1"));
    persons.push_back(Person("ab", "女", "66"));
    persons.push_back(Person("abc", "男", "166"));
    persons.push_back(Person("b", "男", "61"));
    persons.push_back(Person("bc", "女", "16"));
    persons.push_back(Person("bcd", "男", "21"));
    persons.push_back(Person("c", "女", "88"));
    persons.push_back(Person("cd", "男", "101"));
    persons.push_back(Person("cde", "女", "102"));

    list<Filter *> filters;

    // 第一个字母是a
    Filter *filter = new Name_Filter("a");
    print_Persons(filter->filter(persons));
    filters.push_back(filter->clone());
    delete filter;
    cout << endl;

    // 男性
    filter = new Gender_Filter("男");
    print_Persons(filter->filter(persons));
    filters.push_back(filter->clone());
    delete filter;
    cout << endl;

    filter = new WorkNum_Filter("6");
    print_Persons(filter->filter(persons));
    filters.push_back(filter->clone());
    delete filter;
    cout << endl;

    filter = new List_Filter(filters);
    print_Persons(filter->filter(persons));
    delete filter;
    filter = NULL;

    return 0;
}
