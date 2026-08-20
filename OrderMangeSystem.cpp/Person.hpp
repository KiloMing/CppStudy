//person.hpp

#pragma once 

#include <string>
#include <vector>


class Order;
class Room;
class Student;
class Teacher;
class Database;


class Person 
{
    public:
        Person(std::string name, std::string id);
        friend void set_password(Person &p, std::string password);
        void get_information(void);
        bool password_compare(std::string input_password);
        void update_information(std::ostream& out);
        ~Person() = default;
    public:
        std::string name;
        std::string id;
    private:
        std::string password;
};

class Student : public Person
{
    public:
        Student(const std::string& name, const std::string& id): Person(name, id) {}
        void student_menu(void);
        void apply_order(void);
        void show_my_order(void);
        void cancel_order(void);
        void show_all_order(void);
    public:
        std::vector<Order> my_orders;
        int order_number = 0; // To keep track of the number of orders made by the student
};

class Teacher : public Person
{
    public:
        Teacher(const std::string& name, const std::string& id): Person(name, id) {}
        void teacher_menu(void);
        void audit_order(void);
        void show_all_order(void);
};

class Administrator : public Person
{   
    public:
        Administrator(const std::string& name, const std::string& id): Person(name, id) {}
        void administrator_menu(Administrator& admin);
        void add_new_account(void);
        void show_account(void);
        //void show_room(void);
        void clear_order_file(void);
    
    public:
};

class Order
{
    public:
        Order(int order_room_id, std::string student_name, std::string status,
              std::string weekday, std::string time, int order_number, std::string student_id);
    public:
        int order_room_id;
        int order_number;
        std::string student_name;
        std::string student_id;
        std::string status; // e.g., "auditing", "approved", "rejected", "canceled"
        std::string weekday; // e.g., "monday", "Tuesday", etc._123450=78xcf 
        std::string time; //e.g., morning, afternoon;

};

enum class OrderStatus
{
    Auditing,
    Approved,
    Rejected,
    Canceled,
};

class Room
{
    public:
        Room(int room_id, int room_capacity);
        void set_retired_capacity(int retired_capacity);
        void add_room(int room_id, int room_capacity);
    public:
        int room_id;
        int retired_capacity;
        int room_capacity;
};

class Database
{
    public:
        static std::vector<Student> g_students;
        static std::vector<Teacher> g_teachers;
        static Administrator g_administrators;
        static std::vector<Order> g_orders;
        static std::vector<Room> g_rooms;
    public:
        static void initialize_database();
};

void show_room(void);
void sys_login(void);
void data_update(void);
