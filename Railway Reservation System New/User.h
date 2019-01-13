#pragma once
#include <iostream>
#include "Admin.h"

class User
{
public:	
	void GetDetail()
	{
		std::cout << "Enter the username: ";
		std::cin >> username;
		std::cout << "Enter the password: ";
		std::cin >> password;
	}
	void MakeReservation(Admin& admin)
	{
		std::cout << "The information about the travel are: \n\n";
		admin.DisplayTravelSchedules();
		std::cout << "\nEnter the travel id for the train you want to book: ";
		int travelId;
		std::cin >> travelId;
		if (admin.SearchSchedule(travelId) == -1)
			std::cout << "invalid id!\n\n";
		else
		{
			int nSeats;
			char class_;
			std::cout << "Enter the no of seats: ";
			std::cin >> nSeats;
			std::cout << "Enter 'f' for first class and 's' for standard: ";
			std::cin >> class_;
			admin.DeductAvailSeatsFor(travelId, nSeats, class_);
		}

	}
private:
	constexpr static int maxSize = 30;
	char username[maxSize];
	char password[maxSize];

};