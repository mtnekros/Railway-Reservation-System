#include <iostream>
#include <ctime>
#include <string>
#include "TrainTravelSchedule.h"
#include "Admin.h"
#include "User.h"

void AdminMode(Admin& admin)
{
	char answer[30];
	std::cout << "Enter the password: ";
	std::cin >> answer;
	char password[30] = "password";
	if (strcmp(answer, password) != 0)
	{
		std::cout << "Wrong password!\n\n";
		return;
	}
	std::cout << std::endl;
	do
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ADMIN MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
		std::cout << "\t# Enter 1 to Add New Travel Schedule\n";
		std::cout << "\t# Enter 2 to Remove Travel Schedule\n";
		std::cout << "\t# Enter 3 to Display All Travel Schedules\n";
		std::cout << "\t# Enter 4 to Display All User Accounts\n";
		std::cout << "\t# Enter 0 to exit\n";
		std::cout << "\t# Enter your Choice: ";
		int response;
		std::cin >> response;
		std::cout << std::endl;
		switch (response)
		{
		case 1:
			admin.AddTravelSchedule();
			break;
		case 2:
			admin.RemoveTravelSchedule();
			break;
		case 3:
			admin.DisplayTravelSchedules();
			break;
		case 4:
			admin.DisplayUserAccounts();
			break;
		case 0:
			return;
		default:
			std::cout << "Enter 0-4 for options\n\n";
		}
	} while (true);
}
void UserMode(Admin& admin)
{
	char response;
	std::cout << "Do you have an account? ('y' if yes or 'n' to sign up): ";
	std::cin >> response;
	if (response == 'y')
	{
		char username[30];
		char password[30];
		std::cout << "Enter your username: ";
		std::cin >> username;
		int index = admin.SearchUser(username);
		if (index == -1)
		{
			std::cout << "\nSuch a username doesn't exist in the database.\n\n";
			return;
		}
		else
		{
			std::cout << "Enter your password: ";
			std::cin >> password;
			User& user = admin.GetUser(index);
			if (strcmp(password, user.GetPassword()) != 0)
			{
				std::cout << "***Wrong Password!***\n\n";
			}
			else
			{
				std::cout << std::endl;
				do
				{
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~USER MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
					std::cout << "\t# Enter 1 to Make a Reservation.\n";
					std::cout << "\t# Enter 2 to Cancel a Reservation.\n";
					std::cout << "\t# Enter 3 to Display All Travel Schedules\n";
					std::cout << "\t# Enter 4 to Display Your Information\n";
					std::cout << "\t# Enter 0 to return\n";
					std::cout << "\t# Enter your Choice: ";
					int response;
					std::cin >> response;
					std::cout << std::endl;
					switch (response)
					{
					case 1:
						user.MakeReservation(admin);
						break;
					case 2:
						user.CancelReservation(admin);
						break;
					case 3:
						admin.DisplayTravelSchedules();
						break;
					case 4:
						user.PrintInFoForUser(admin);
						std::cout << std::endl;
						break;
					case 0:
						return;
					default:
						std::cout << "Enter 0-4 for options\n\n";
					}
				} while (true);
			}

		}
		
	}
	else if (response == 'n')
	{
		std::cout << "Sign Up:\n";
		admin.AddUser();
	}
	else
	{
		std::cout << "Invalid Response!\n\n";
	}
}
int main()
{
	Admin admin;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "...............WELCOME TO RAILWAY RESERVATION SYSTEM...............\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	do
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
		std::cout << "\t# Enter 1 for Admin mode\n";
		std::cout << "\t# Enter 2 for User mode\n";
		std::cout << "\t# Enter 0 for Exit\n";
		std::cout << "\t# Enter your choice: ";
		int response;
		std::cin >> response;
		std::cout << std::endl;
		switch (response)
		{
		case 1:
			AdminMode(admin);
			break;
		case 2:
			UserMode(admin);
			break;
		case 0:
			return 0;
		default:
			std::cout << "Enter 0-2 for options\n\n";
		}
	} while (true);

	system("pause");
	return 0;
}