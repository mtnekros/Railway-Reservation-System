#include <iostream>
#include <ctime>
#include "TrainDetails.h"
/*
int main()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << ".......WELCOME TO RAILWAY RESERVATION SYSTEM..........\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	do
	{
		std::cout << "^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^^^^\n\n";
		std::cout << "Enter 1 for Admin mode\nEnter 2 for User mode\nEnter 3 for Exit\n";
		std::cout << "Enter your choice:";
		char response;
		std::cin >> response;
		std::cout << std::endl;
		switch (response)

		{
		case 1:
			std::cout << "Admin Stuff here\n";
			break;
		case 2:
			std::cout << "User Stuff here\n";
			break;
		case 3:
			return 0;
		default:
			std::cout << "Enter 1-3 for options\n\n";
		}
	} while (true);

	system("pause");
	return 0;
}

*/

int main()
{
	Train train;
	train.getdetail();
	train.printDetail();
	system("pause");
}