#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Staff;


static Staff* staffnumber[100]; //员工数组
static int staff_count = 0; //员工数量

/*创建成员类*/
class Staff
{
    public:
    
    virtual void staff_data(string name, int age, string position, int id) = 0; //纯虚函数
    virtual void staff_work(string work) = 0; //纯虚函数
    virtual ~Staff() {} //虚析构函数，确保派生类对象被正确销毁

    string name;
    int age;
    string position;
    int id; //员工编号
    string work; //员工工作内容
};

class Employee : public Staff
{
    public: 
    void staff_data(string name, int age, string position, int id)
    {
        this->name = name;
        this->age = age;
        this->position = position;
        this->id = id;
    }
    void staff_work(string work)
    {
        this->work = work;
    }
};

class Manager : public Staff
{
    public:
    void staff_data(string name, int age, string position, int id)
    {
        this->name = name;
        this->age = age;
        this->position = position;
        this->id = id;
    }
    void staff_work(string work)
    {
        this->work = work;
    }
};

class Boss : public Staff
{
    public:
    void staff_data(string name, int age, string position, int id)
    {
        this->name = name;
        this->age = age;
        this->position = position;
        this->id = id;
    }
    void staff_work(string work)
    {
        this->work = work;
    }
};
/*添加员工信息*/
void add_staff(string name, int age, string position, int id)
{
    Staff* t_staff = nullptr;
    if (position == "员工") {
        t_staff = new Employee();
    } else if (position == "经理") {
        t_staff = new Manager();
    } else if (position == "老板") {
        t_staff = new Boss();
    }
    t_staff->staff_data(name, age, position, id);
    staffnumber[staff_count] = t_staff;
    staff_count++;
    t_staff->staff_work("无");
}

/*显示员工信息*/
void show_staff(void){
    for (int i = 0; i < staff_count; i++)
    {
        cout << "员工姓名：" << staffnumber[i]->name << " 员工年龄：" << staffnumber[i]->age 
             << " 员工职位：" << staffnumber[i]->position << " 员工工作内容：" << staffnumber[i]->work << endl;
    }
    if (staff_count == 0)
    {
        cout << "没有员工信息" << endl;
    }
}

/* 查找员工信息 名字 */
Staff* find_staff(string name)
{
    for (int i = 0; i < staff_count; i++)
    {
        if (staffnumber[i]->name == name)
        {
            cout << "查询成功" << endl;
            cout << "员工姓名：" << staffnumber[i]->name << " 员工年龄：" << staffnumber[i]->age << " 员工职位：" << staffnumber[i]->position << endl;
            return staffnumber[i]; // 返回找到的员工指针    
        }
    }
    cout << "没有找到该员工信息" << endl;
    return nullptr; // 未找到员工返回空指针

}
/* 查找员工信息 编号 */
Staff* find_staff(int id)
{
    for (int i = 0; i < staff_count; i++)
    {
        if (staffnumber[i]->id == id)
        {
            cout << "查询成功" << endl;
            cout << "员工姓名：" << staffnumber[i]->name << " 员工年龄：" << staffnumber[i]->age 
            << " 员工职位：" << staffnumber[i]->position << " 员工工作内容：" << staffnumber[i]->work << endl;
            return staffnumber[i]; // 返回找到的员工指针
        }
    }
    cout << "没有找到该员工信息" << endl;
    return nullptr; // 未找到员工返回空指针

}

/* 删除员工信息 */
void delete_staff(int id)
{
    for (int i = 0; i < staff_count; i++)
    {
        if (staffnumber[i]->id == id)
        {
            for (int j = i; j < staff_count - 1; j++)
            {
                staffnumber[j] = staffnumber[j + 1];
            }
            staff_count--;
            cout << "删除成功" << endl;
            return;
        }
    }
    cout << "没有找到该员工信息" << endl;
    return;
}

/*使用名字进行删除*/
void delete_staff(string name)
{
    for (int i = 0; i < staff_count; i++)
    {
        if (staffnumber[i]->name == name)
        {
            for (int j = i; j < staff_count - 1; j++)
            {
                staffnumber[j] = staffnumber[j + 1];
            }
            staff_count--;
            cout << "删除成功" << endl;
            return;
        }
    }
    
    cout << "没有找到该员工信息" << endl;
}
//修改信息 id
void modify_staff(Staff *staff_ptr){
    string m_name;
    int m_age;
    string m_position;  
    int m_id;
    int temp_index = -1;
    if (staff_ptr == nullptr)
    {
        cout << "未找到该员工信息" << endl;
        return;
    }
    if (staff_ptr != nullptr)
    {
        cout << "请输入新的员工姓名：" << endl;
        cin >> m_name;
        cout << "请输入新的员工年龄：" << endl;
        cin >> m_age;
        cout << "请输入新的员工职位（员工/经理/老板）：" << endl;
        cin >> m_position;
        cout << "请输入新的员工编号：" << endl;
        cin >> m_id;
        if (m_position == "员工")
        {
            staff_ptr->staff_data(m_name, m_age, m_position, m_id);
            cout << "修改成功" << endl;
        }
        else if (m_position == "经理")
        {
            staff_ptr->staff_data(m_name, m_age, m_position, m_id);
            cout << "修改成功" << endl;
        }
        else if (m_position == "老板")
        {
            staff_ptr->staff_data(m_name, m_age, m_position, m_id);
            cout << "修改成功" << endl;
        }
        else
        {
            cout << "职位输入有误，请重新输入" << endl;
            cin >> m_position;
            modify_staff(staff_ptr); // 递归调用，重新修改员工信息
            return; // 递归调用后返回，避免继续执行下面的代码
        }

    }
}

/*
 * 员工管理系统
 * 1、创建一个员工管理系统
 * 2、可以添加员工
 * 3、显示员工
 * 4、按照编号查找员工
 * 5、按照编号删除员工
 * 6、按照编号修改员工信息
 * 7、退出系统
 */
void menu()
{
    cout << "*********************************" << endl;
    cout << "*********  欢迎使用员工管理系统  *********" << endl;
    cout << "*********  1、添加员工信息      *********" << endl;
    cout << "*********  2、显示员工信息      *********" << endl;
    cout << "*********  3、查找员工信息      *********" << endl;
    cout << "*********  4、删除员工信息      *********" << endl;
    cout << "*********  5、修改员工信息      *********" << endl;
    cout << "*********  6、清空所有文档      *********" << endl;
    cout << "*********  7、退出系统          *********" << endl;
    cout << "*********************************" << endl;
}


int main() {
    string a_name;
    int a_age;
    string a_position;
    int a_id;
    fstream file;
    int file_employee_count = 0;
    int file_manager_count = 0;
    int file_boss_count = 0;
    file.open("staffdata.txt", ios::in);

    if (file.is_open())
    {
        file >> file_employee_count
             >> file_manager_count
             >> file_boss_count;

        for (int i = 0; i < file_employee_count; i++)
        {
            file >> a_name >> a_age >> a_position >> a_id;
            add_staff(a_name, a_age, a_position, a_id);
        }

        for (int i = 0; i < file_manager_count; i++)
        {
            file >> a_name >> a_age >> a_position >> a_id;
            add_staff(a_name, a_age, a_position, a_id);
        }

        for (int i = 0; i < file_boss_count; i++)
        {
            file >> a_name >> a_age >> a_position >> a_id;
            add_staff(a_name, a_age, a_position, a_id);
        }

    file.close();
    }
    cout << "员工信息加载完成" << endl;
    menu();
    cout << "请输入您的选择：" << endl;
    int choice = 0;
    cin >> choice;
    while (1)
    {   
        menu();
        switch (choice)
        {
        case 1:
            /* 添加员工信息的代码 */
            
            cout << "请输入员工姓名：" << endl;
            cin >> a_name;
            cout << "请输入员工年龄：" << endl;
            cin >> a_age;
            cout << "请输入员工职位（员工/经理/老板）：" << endl;
            cin >> a_position;
            cout << "请输入员工编号：" << endl;
            cin >> a_id;
            add_staff(a_name, a_age, a_position, a_id);
            break;
        case 2:
            /* 显示员工信息的代码 */
            show_staff();
            break;
        case 3:
            /* 查找员工信息的代码 */
            cout << "请输入查找方式（1、按姓名查找 2、按编号查找）：" << endl;
            int find_choice;
            cin >> find_choice;
            if (find_choice == 1)
            {
                cout << "请输入员工姓名：" << endl;
                cin >> a_name;
                find_staff(a_name);
            }
            else if (find_choice == 2)
            {
                cout << "请输入员工编号：" << endl;
                cin >> a_id;
                find_staff(a_id);
            }
            else
            {
                cout << "输入有误，请重新输入：" << endl;
            }
            break;
        case 4:
            /* 删除员工信息的代码 */
            cout << "请输入删除方式（1、按姓名删除 2、按编号删除）：" << endl;
            int delete_choice;
            cin >> delete_choice;
            if (delete_choice == 1)
            {
                cout << "请输入员工姓名：" << endl;
                cin >> a_name;
                delete_staff(a_name);
            }
            else if (delete_choice == 2)
            {
                cout << "请输入员工编号：" << endl;
                cin >> a_id;
                delete_staff(a_id);
            }
            else
            {
                cout << "输入有误，请重新输入：" << endl;
            }
            break;
        case 5:
            /* 修改员工信息的代码 */
            cout << "请输入修改方式（1、按姓名修改 2、按编号修改）：" << endl;
            int modify_choice;
            cin >> modify_choice;
            if (modify_choice == 1)
            {
                cout << "请输入员工姓名：" << endl;
                cin >> a_name;
                modify_staff(find_staff(a_name));
            }
            else if (modify_choice == 2)
            {
                cout << "请输入员工编号：" << endl;
                cin >> a_id;
                modify_staff(find_staff(a_id));
            }
            else
            {
                cout << "输入有误，请重新输入：" << endl;
            }
            break;
        case 6:
            /* 清空所有文档的代码 */
            break;
        case 7:
            /* 退出系统的代码 */
            file.open("staffdata.txt", ios::out);

            file  << staff_count << endl;
            for(int i = 0; i < staff_count; i++)
            {
                file << staffnumber[i]->name << " " << staffnumber[i]->age << " " << staffnumber[i]->position << " " << staffnumber[i]->id << endl;
            }
            file.close();   
            return 0;
        default:
            cout << "输入有误，请重新输入：" << endl;
            break;
        }
        cout << "请输入您的选择：" << endl;
        cin >> choice;
    }
    return 0;
}