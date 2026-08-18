/*
3.10.1 案例描述
公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
员工信息有: 姓名 工资组成；部门分为：策划、美术、研发
随机给10名员工分配部门和工资
通过multimap进行信息的插入 key(部门编号) value(员工)
分部门显示员工信息
3.10.2 实现步骤
创建10名员工，放到vector中
遍历vector容器，取出每个员工，进行随机分组
分组后，将员工部门编号作为key，具体员工作为value，放入到multimap容器中
分部门显示员工信息
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Person
{
    public:
        Person(string name, int id, string department, int salary)
        {
            this->name = name;
            this->id = id;
            this->department = department;
            this->salary = salary;
        }

    public:
        string name;
        int id;
        string department;
        int salary;
};

int main(void){
    vector<Person> p;
    string name;
    int id;
    string department;
    int salary;
    for(int i = 0; i < 10; i++){
        cin >> name >> id >> department >> salary;
        p.emplace_back(name, id, department, salary);
    }
    set<Person> art;
    set<Person> scheme;
    set<Person> study;

    for(auto it = p.begin(); it != p.end(); it++)
    {
        if(it->department == "art")
        {
            art.insert(*it);
        }
        else if(it->department == "scheme")
        {
            scheme.insert(*it);
        }
        else {
            study.insert(*it);
        }
    }
    map<int, set<Person>>m1;
    m1[1] = art;
    m1[2] = scheme;
    m1[3] = study;
}