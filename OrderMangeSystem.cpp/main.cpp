#include <iostream>
#include "Person.hpp"

int main(void)
{
    Database::initialize_database(); // Initialize the database with sample data
    std::cout << "Welcome to the Order Management System!" << std::endl;

	std::cout << "======================  Welcome to the Order Management System!  =====================" 
         << std::endl;
	std::cout << std::endl << "Please select your role: " << std::endl;
	std::cout << "\t\t -------------------------------\n";
	std::cout << "\t\t|                               |\n";
	std::cout << "\t\t|          1. Student           |\n";
	std::cout << "\t\t|                               |\n";
	std::cout << "\t\t|          2. Teacher           |\n";
	std::cout << "\t\t|                               |\n";
	std::cout << "\t\t|          3. Administrator     |\n";
	std::cout << "\t\t|                               |\n";
	std::cout << "\t\t|          0. Exit              |\n";
	std::cout << "\t\t|                               |\n";
	std::cout << "\t\t -------------------------------\n";
	std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;
    while (true)
    {
        switch (choice)
        {
            case 1:
                // Create a Student object and call its methods
                sys_login();
                break;
            case 2:
                // Create a Teacher object and call its methods
                sys_login();
                break;
            case 3:
                // Create an Administrator object and call its methods
                sys_login();
                break;
            case 0:
                std::cout << "Exiting the system. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}