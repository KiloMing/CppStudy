
#include <iostream>
#include "Person.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
/********PUBLIC***********/ // Global database containing all students, teachers, administrators, orders, and rooms

namespace
{
    const std::string DATA_DIRECTORY =
        "/Users/a1-6/Desktop/CPP_STUDY/OrderMangeSystem.cpp/Data/";
}

std::vector<Student> Database::g_students{};
std::vector<Teacher> Database::g_teachers{};
Administrator Database::g_administrators{"Admin", "admin123"};
std::vector<Order> Database::g_orders{};
std::vector<Room> Database::g_rooms{};

void Database::initialize_database()
{
    // Initialize the database with some sample data
    g_administrators = Administrator("Admin", "admin123");
    set_password(g_administrators, "adminpass");
    std::ifstream student_file(DATA_DIRECTORY + "student_account.txt");
    if (student_file.is_open())
    {
        std::string name, id, password;
        while (student_file >> name >> id >> password)
        {
            g_students.emplace_back(name, id);
            set_password(g_students.back(), password);  
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "student_account.txt for reading." << std::endl;
    }
    student_file.close();
    std::ifstream teacher_file(DATA_DIRECTORY + "teacher_account.txt");
    if (teacher_file.is_open())
    {
        std::string name, id, password;
        while (teacher_file >> name >> id >> password)
        {
            g_teachers.emplace_back(name, id);
            set_password(g_teachers.back(), password);
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "teacher_account.txt for reading." << std::endl;
    }
    teacher_file.close();
    std::ifstream room_file(DATA_DIRECTORY + "room.txt");
    if (room_file.is_open())
    {
        int room_id, room_capacity, retired_capacity;
        while (room_file >> room_id >> room_capacity >> retired_capacity)
        {
            g_rooms.emplace_back(room_id, room_capacity);
            g_rooms.back().set_retired_capacity(retired_capacity);
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "room.txt for reading." << std::endl;
    }
    room_file.close();
    std::ifstream order_file(DATA_DIRECTORY + "order.txt");
    if (order_file.is_open())
    {
        int order_room_id, order_number;
        std::string student_name, status, weekday, time, student_id;        
        while (order_file >> order_room_id >> student_name >> status >> weekday >> time >> order_number >> student_id)
        {
            g_orders.emplace_back(order_room_id, student_name, status, weekday, time, order_number, student_id);
            
            auto student_it = std::find_if(g_students.begin(), g_students.end(), [student_id](const Student& student) {
                return student.id == student_id;
            });
            if (student_it != g_students.end())
            {
                student_it->my_orders.push_back(g_orders.back());
                student_it->order_number++; // Increment the order number for the student   
            }

        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "order.txt for reading." << std::endl;
    }
    order_file.close();

}
/*************PERSON*******************/

// Set the password for a Person object
Person::Person(std::string name, std::string id)
{
    this->name = name;
    this->id = id;
}

void set_password(Person &p, std::string password)
{
    p.password = password;
}

// show out the information of a Person object
void Person::get_information(void)
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
}

bool Person::password_compare(std::string input_password)
{
    if (input_password == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Person::update_information(std::ostream& out)
{
    out << name << " " << id << " " << password << std::endl;
}

/*************STUDENT*******************/
void Student::student_menu(void)
{
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Student Menu:" << std::endl;
        std::cout << "1. Apply for an order" << std::endl;
        std::cout << "2. Show my orders" << std::endl;
        std::cout << "3. Show all orders" << std::endl;
        std::cout << "4. Cancel an order" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << std::endl;
        // Here you would typically implement the logic to handle the student's menu choices
        int st_choice;
        std::cout << "Enter your choice: ";
        std::cin >> st_choice;
        std::cout << std::endl;
        switch (st_choice)
        {
            case 1:
                apply_order();
                std::cout << std::endl;

                break;
            case 2:
                show_my_order();
                std::cout << std::endl;
                break;  
            case 3:
                show_all_order();
                std::cout << std::endl;
                break;
            case 4:
                cancel_order();
                std::cout << std::endl;
                break;
            case 0:
                std::cout << std::endl;
                return;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cout << std::endl;
                break;
        }
    }
}


// apply for an order and add it to the global order list
void Student::apply_order(void)
{
    show_room();
    int room_id;
    std::cout << std::endl;
    std::cout << "Applying for an order..." << std::endl;
    // Implementation for applying an order
    std::cout << "Enter the room ID you want to order: ";
    std::cin >> room_id;
    std::cout << std::endl;
    auto room_it = std::find_if(Database::g_rooms.begin(), Database::g_rooms.end(), [room_id](const Room& room) {
        return room.room_id == room_id;
    });
    if (room_it == Database::g_rooms.end())
    {
        std::cout << "Room not found." << std::endl;
        return;
    }else
    {
        if(room_it->retired_capacity <= 0)
        {
            std::cout << "Room is fully booked. Cannot apply for this room." << std::endl;
            return;
        }
    }

    std::string day;
    std::cout << "Enter the day for the order (e.g., Monday): ";
    std::cin >> day;

    std::string time;
    std::cout << "Enter the time for the order (e.g., morning, afternoon): ";
    std::cin >> time;
    std::cout << std::endl;
    Order s_order(room_id, name, "auditing", day, time, this->order_number, id);
    my_orders.push_back(s_order);
    Database::g_orders.push_back(s_order);
    std::cout << "Order applied successfully!" << std::endl;
    this->order_number++;  //Only plus the order_number when the Order applied successfully.
    room_it->retired_capacity--; // Decrement the retired capacity of the room
}

//show out the orders of the student
void Student::show_my_order(void)
{
    if (my_orders.empty())
    {
        std::cout << "You have no orders." << std::endl;
        return;
    }
    std::cout << "My Orders:" << std::endl;
    for (auto &order : my_orders)
    {
        
        std::cout << "Order Number: " << order.order_number
                  << ", Room ID: " << order.order_room_id 
                  << ", Status: " << order.status 
                  << ", Day: " << order.weekday 
                  << ", Time: " << order.time << std::endl;
    }
    std::cout << std::endl;
}   

// cancel an order by order number
void Student::cancel_order(void)
{
    if (my_orders.empty())
    {
        std::cout << "You have no orders to cancel." << std::endl;
        return;
    }
    int order_number;
    std::cout << "Enter the Order Number of the order you want to cancel: ";
    std::cin >> order_number;
    auto it = std::find_if(my_orders.begin(), my_orders.end(), [order_number](const Order& order) {
        return order.order_number == order_number;
    });
    if (it != my_orders.end())
    {
        it->status = "canceled"; // Update the status to "canceled"
        // Also remove from the global order list
        auto global_it = std::find_if(Database::g_orders.begin(), Database::g_orders.end(), [order_number](const Order& order) {
            return order.order_number == order_number;
        });
        if (global_it != Database::g_orders.end())
        {
            global_it->status = "canceled"; // Update the status to "canceled" in the global list
        }
        std::cout << "Order canceled successfully!" << std::endl;
    }
    else
    {
        std::cout << "Order not found." << std::endl;
    }
}

//show out all the orders in the global order list
void Student::show_all_order(void)
{
    if (Database::g_orders.empty())
    {
        std::cout << "No orders available." << std::endl;
        return;
    }
    std::cout << "All Orders:" << std::endl;
    for (auto &order : Database::g_orders)
    {
        std::cout << "Room ID: " << order.order_room_id 
                  << ", Student Name: " << order.student_name 
                  << ", Status: " << order.status 
                  << ", Day: " << order.weekday 
                  << ", Time: " << order.time << std::endl;
    }
    std::cout << std::endl;
}



/*************TEACHER*******************/
void Teacher::teacher_menu(void)
{
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Teacher Menu:" << std::endl;
        std::cout << "1. Show all orders" << std::endl;
        std::cout << "2. Audit an order" << std::endl;
        std::cout << "0. Exit" << std::endl;
        // Here you would typically implement the logic to handle the teacher's menu choices
        std::cout << std::endl;
        int te_choice;
        std::cout << "Enter your choice: "; 
        std::cin >> te_choice;
        std::cout << std::endl;
        switch(te_choice)
        {
            case 1:
                show_all_order();
                std::cout << std::endl;
                break;
            case 2:
                audit_order();
                std::cout << std::endl;
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cout << std::endl;
                break;
        }
    }
}

//show out all the orders in the global order list
void Teacher::show_all_order(void)
{
    if (Database::g_orders.empty())
    {
        std::cout << "No orders available." << std::endl;
        return;
    }
    std::cout << "All Orders:" << std::endl;
    for (auto &order : Database::g_orders)
    {
        std::cout << "Room ID: " << order.order_room_id 
                  << ", Order Number: " << order.order_number
                  << ", Student Name: " << order.student_name
                  << ", Student ID: " << order.student_id
                  << ", Status: " << order.status 
                  << ", Day: " << order.weekday 
                  << ", Time: " << order.time << std::endl;
    }
    std::cout << std::endl;
}

// Audit an order by student ID and Order Number update its status
void Teacher::audit_order(void)
{
    if(Database::g_orders.empty())
    {
        std::cout << "No orders to audit." << std::endl;
        return;
    }
    std::string student_id;
    std::cout << "Enter the student ID to audit: ";
    std::cin >> student_id;
    int student_order_number;
    std::cout << "Enter the order number to audit: ";
    std::cin >> student_order_number;
    std::cout << std::endl;
    bool found = false;
    for (auto &order : Database::g_orders)
    {
        if (order.student_id == student_id && order.order_number == student_order_number && order.status == "auditing")
        {
            found = true;
            std::cout << "Order Number: " << order.order_number 
                      << ", Order found: Room ID: " << order.order_room_id 
                      << ", Student Name: " << order.student_name 
                      << ", Status: " << order.status 
                      << ", Day: " << order.weekday 
                      << ", Time: " << order.time << std::endl;
            std::cout << "Enter new status (approved/rejected): ";
            std::string new_status;
            std::cin >> new_status;
            std::cout << std::endl;
            auto it = std::find_if(Database::g_students.begin(), Database::g_students.end(), [student_id](const Student& student) {
                return student.id == student_id;
            });
            if (new_status == "approved" || new_status == "rejected")
            {
                order.status = new_status;
                std::cout << "Order status updated to " << new_status << "." << std::endl;
               
                //find the autited student , the student_it must be fined because the "if" in line 258.
                auto student_it = std::find_if(it->my_orders.begin(), it->my_orders.end(), [student_order_number](const Order& order) {
                        return order.order_number == student_order_number;
                });
                auto room_it = std::find_if(Database::g_rooms.begin(), Database::g_rooms.end(), [order](const Room& room) {
                    return room.room_id == order.order_room_id;
                });

                if(new_status == "approved")
                {

                    if (student_it != it->my_orders.end())
                    {
                        student_it->status = "approved";
                        std::cout << "Order approved successfully!" << std::endl;
                        std::cout << std::endl;
                    }
                }
                else if(new_status == "rejected")
                {
                    if (student_it != it->my_orders.end())
                    {
                        student_it->status = "rejected";
                        std::cout << "Order rejected successfully!" << std::endl;
                        std::cout << std::endl;
                    }
                    if(room_it != Database::g_rooms.end())
                    {
                        room_it->retired_capacity++; // Increment the retired capacity of the room
                    }
                }
            }
            else
            {
                std::cout << "Invalid status. No changes made." << std::endl;
                std::cout << std::endl;
            }
            break;
        }
    }
    if (!found)
    {
        std::cout << "Order not found." << std::endl;
        std::cout << std::endl;
    }
}

/*************ADMINISTRATOR*******************/
//constructor for Administrator class

void Administrator::administrator_menu(Administrator& admin)
{
    while(true)
    {

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Administrator Menu:" << std::endl;
        std::cout << "1. Add new account" << std::endl;
        std::cout << "2. Show accounts" << std::endl;
        std::cout << "3. Show rooms" << std::endl;
        std::cout << "4. Clear order file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << std::endl;
        // Here you would typically implement the logic to handle the administrator's menu choices
        int ad_choice;
        std::cout << "Enter your choice: ";
        std::cin >> ad_choice;
        std::cout << std::endl;
        switch (ad_choice)
        {
            case 1:
                admin.add_new_account();
                break;
            case 2:
                admin.show_account();
                break;
            case 3:
                show_room();
                break;
            case 4:
                admin.clear_order_file();
                break;
            case 0:
                return;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void Administrator::add_new_account(void)
{
    std::cout << "Enter the role of the new account (student/teacher): ";
    std::string name;
    std::string id;
    std::string password;
    std::string role;
    bool account_created = false;
    std::cin >> role;
    std::cout << std::endl;
    if(role == "student")
    {
        std::cout << "Enter the name of the new student account: ";
        std::cin >> name;
        std::cout << "Enter the ID of the new student account: ";
        std::cin >> id;
        std::cout << "Enter the password for the new student account: ";
        std::cin >> password;
        std::cout << std::endl;
        Database::g_students.emplace_back(name, id);
        set_password(Database::g_students.back(), password);
        std::cout << std::endl;

    }
    else if(role == "teacher")
    {
        std::cout << "Enter the name of the new teacher account: ";
        std::cin >> name;
        std::cout << "Enter the ID of the new teacher account: ";
        std::cin >> id;
        std::cout << "Enter the password for the new teacher account: ";
        std::cin >> password;
        std::cout << std::endl;
        Database::g_teachers.emplace_back(name, id);
        set_password(Database::g_teachers.back(), password);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Invalid role. Please enter 'student' or 'teacher'." << std::endl;
        return;
    }
    // Here you would typically add code to save this information to a database or file
    std::cout << "New account created successfully!" << std::endl;
    std::cout << std::endl;
}

void Administrator::show_account(void)
{
    std::cout << "Student Accounts:" << std::endl;
    for (auto &student : Database::g_students)
    {
        student.get_information();
    }
    std::cout << std::endl;
    std::cout << "Teacher Accounts:" << std::endl;
    for (auto &teacher : Database::g_teachers)
    {
        teacher.get_information();
    }
    std::cout << std::endl;

}

void Administrator::clear_order_file(void)
{
    Database::g_orders.clear();
    std::cout << "All orders have been cleared." << std::endl;
}

/**********ORDER **********/
//constructor for Order class
Order::Order(int order_room_id, std::string student_name, std::string status,
             std::string weekday, std::string time, int order_number, std::string student_id)
    : order_room_id(order_room_id), student_name(student_name), status(status),
      weekday(weekday), time(time), order_number(order_number), student_id(student_id)
{
}


/**********ROOM **********/
//constructor for Room class
Room::Room(int room_id, int room_capacity)
    : room_id(room_id), room_capacity(room_capacity), retired_capacity(room_capacity)
{
}

void Room:: set_retired_capacity(int retired_capacity)
{
    this->retired_capacity = retired_capacity;
}

void Room::add_room(int room_id, int room_capacity)
{
    Database::g_rooms.emplace_back(room_id, room_capacity);
    std::cout << "Room added successfully!" << std::endl;
    std::cout << std::endl;
}
/********************/
void  show_room(void)
{
    for(auto &room : Database::g_rooms)
    {
        std::cout << "Room ID: " << room.room_id 
                  << ", Capacity: " << room.room_capacity 
                  << ", Retired Capacity: " << room.retired_capacity << std::endl;
    }
    std::cout << std::endl;
}

void sys_login(void)
{
    std::string id;
    std::string password;
    std::cout << "Enter your ID: ";
    std::cin >> id;
    std::cout << "Enter your password: ";
    std::cin >> password;
    std::cout << std::endl;
    // Check if the ID and password match any student account
    for (auto &student : Database::g_students)
    {
        if (student.id == id && student.password_compare(password))
        {
            std::cout << "Login successful! Welcome, " << student.name << "." << std::endl;\

            student.student_menu();
            std::cout << std::endl;
            return;
        }
    }

    // Check if the ID and password match any teacher account
    for (auto &teacher : Database::g_teachers)
    {
        if (teacher.id == id && teacher.password_compare(password))
        {
            std::cout << "Login successful! Welcome, " << teacher.name << "." << std::endl;
            teacher.teacher_menu();
            std::cout << std::endl;
            return;
        }
    }

    // Check if the ID and password match the administrator account
    if (Database::g_administrators.id == id && Database::g_administrators.password_compare(password))
    {
        std::cout << "Login successful! Welcome, Administrator." << std::endl;
        Database::g_administrators.administrator_menu(Database::g_administrators);
        std::cout << std::endl;
        return;
    }

    std::cout << "Invalid ID or password. Please try again." << std::endl;
    std::cout << std::endl;
}

void data_update(void)
{
    // Update student accounts
    std::ofstream student_file(DATA_DIRECTORY + "student_account.txt");
    if (student_file.is_open())
    {
        for (auto &student : Database::g_students)
        {
            student.update_information(student_file);
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "student_account.txt for writing." << std::endl;
    }
    student_file.close();

    // Update teacher accounts
    std::ofstream teacher_file(DATA_DIRECTORY + "teacher_account.txt");
    if (teacher_file.is_open())
    {
        for (auto &teacher : Database::g_teachers)
        {
            teacher.update_information(teacher_file);
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "teacher_account.txt for writing." << std::endl;
    }
    teacher_file.close();

    // Update orders
    std::ofstream order_file(DATA_DIRECTORY + "order.txt");
    if (order_file.is_open())
    {
        for (const auto &order : Database::g_orders)
        {
            order_file << order.order_room_id << " " << order.student_name << " " 
                       << order.status << " " << order.weekday << " "
                       << order.time << " " << order.order_number 
                       << " " << order.student_id << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "order.txt for writing." << std::endl;
    }
    order_file.close();

    std::ofstream room_file(DATA_DIRECTORY + "room.txt");
    if (room_file.is_open())
    {
        for (const auto &room : Database::g_rooms)
        {   
            room_file << room.room_id << " " << room.room_capacity << " " << room.retired_capacity << std::endl;
        }   
    }
    else
    {
        std::cerr << "Failed to open " << DATA_DIRECTORY
                  << "room.txt for writing." << std::endl;
    }
    room_file.close();
}
