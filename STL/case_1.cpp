/*
有5名选手：选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
3.4.2 实现步骤
创建五名选手，放到vector中
遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
sort算法对deque容器中分数排序，去除最高和最低分
deque容器遍历一遍，累加总分
获取平均分
*/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
using namespace std;

class Person
{
    public:
    
        Person(string name, int age)
        {
            this->age = age;
            this->name = name;
        }

        void process_original_scores(void)
        {
            cout << "输入这个人的成绩" << endl;
            int t_scores;
            for(int i = 0; i < 10; i++){
                cin >> t_scores;
                original_scores.push_back(t_scores);
            }
            deque<int> temp_dq(original_scores);
            sort(temp_dq.begin(), temp_dq.end());
            temp_dq.pop_back();
            temp_dq.pop_front();
            int temp = 0;
            for(deque<int>::iterator it = temp_dq.begin(); it != temp_dq.end();  it++){
                temp += *it;
            }
            final_scores = temp/8;
        }

        void print_result(void)
        {
            cout << "name:" << name << " " <<  "age:" << age << endl;
            cout << "original scores: ";
            for(auto it = original_scores.begin(); it != original_scores.end(); it++){
                cout << *it << " ";
            }
            cout << endl;
            cout << "final socres: " << final_scores << endl;
            cout << endl;
        }

    public:

        deque<int> original_scores;
        string name;
        int age;
        int final_scores;

};

int main(){
    vector<Person> p;
    string name;
    int age;
    for(int i = 1; i <= 5; i++){
        printf("输入第%d的姓名和年龄", i);
        cin >> name >> age;
        Person p1(name, age);
        p1.process_original_scores();
        p.push_back(p1);
    }
    for(auto it = p.begin(); it != p.end(); it++)
    {
        it->print_result();
    }
}