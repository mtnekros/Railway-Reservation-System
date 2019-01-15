#include "User.h"
#include "Admin.h"
#include <iomanip>

void User::SetUsername(const char* const in_username)
{
	strcpy_s(username, in_username);
}

void User::SetPassword(const char* const in_password)
{
	strcpy_s( password, in_password);
}

void User::MakeReservation(Admin & admin)
{
	if (travelScheduleId == -1)
	{
		std::cout << "The information about the travel are: \n\n";
		admin.DisplayTravelSchedules();
		std::cout << "\nEnter the travel id for the train you want to book: ";
		std::cin >> travelScheduleId;
		int scheduleIndex = admin.SearchSchedule(travelScheduleId);
		if (scheduleIndex == -1)
		{
			std::cout << "invalid id!\n\n";
		}
		else
		{
			std::cout << "Enter the no of seats: ";
			std::cin >> nSeats;
			std::cout << "Enter 'f' for first class and 's' for standard: ";
			std::cin >> class_;
			if (nSeats > admin.GetSchedule(scheduleIndex).GetAvailSeats(class_))
			{
				std::cout << "There aren't " << nSeats << " seats available at the moment. Sorry for your Inconvenience, " << username << ".\n\n";
				return;
			}
			admin.AddAvailSeatsFor(travelScheduleId, -nSeats, class_); //-nSeats for deducting available seats
			std::cout << "\nYou have booked " << nSeats << " " << class_ << "-class seats for the following travel schedule: \n\n";
			admin.DisplayTravelSchedules(travelScheduleId);
			std::cout << "\nTHANK YOU!\n\n";
		}
	}
	else
	{
		std::cout << username << ", you already have a reservation. Cancel it if you want to make a new reservation.\n\n";
	}
}

void User::CancelReservation(Admin & admin)
{
	int index = admin.SearchSchedule(travelScheduleId);
	if (index != -1)
	{
		std::cout << "You have registered for the following train schedule:\n\n";
		admin.DisplayTravelSchedules(travelScheduleId);
		char response;
		std::cout << "Are you sure you want to cancel?('y' or 'n'): ";
		std::cin >> response;
		if (response == 'y')
		{
			admin.AddAvailSeatsFor(travelScheduleId, nSeats, class_);
			travelScheduleId = -1;
			nSeats = 0;
			class_ = '0';
		}
		else
		{
			std::cout << "\nYour cancellation has been cancelled.\n";
		}
	}
	else
	{
		std::cout << "\nYou have no reservations to cancel," << username << ".\n\n";
	}
}

void User::Deserialize(std::ifstream & in)
{
	in.read(reinterpret_cast<char*>(this), sizeof(*this));
}

void User::Serialize(std::ofstream & out) const
{
	out.write(reinterpret_cast<const char*>(this), sizeof(*this));
}

void User::PrintTitles()
{
	using namespace std;
	const int sm_w = 13;
	const int bg_w = 18;
	const std::string bg_tw = "------------------";
	const std::string sm_tw = "-------------";
	std::string cls = "class";
	cout << "+" << bg_tw << "+" << bg_tw << "+" << bg_tw << "+" << sm_tw << "+" << sm_tw << "+" << "\n";
	cout << '|' << setw(bg_w) << "username" << '|' << setw(bg_w) << "password" << '|' << setw(bg_w) << "travelScheduleId" << '|' << setw(sm_w) << "no Of Seats" << '|' << setw(sm_w) << "class"<< "|\n";
	cout << "+" << bg_tw << "+" << bg_tw << "+" << bg_tw << "+" << sm_tw << "+" << sm_tw << "+" << "\n";

}

void User::PrintInfoForAdmin() const
{
	using namespace std;
	const int sm_w = 13;
	const int bg_w = 18;
	cout << '|' << setw(bg_w) << username << '|' << setw(bg_w) << password << '|' << setw(bg_w) << travelScheduleId << '|' << setw(sm_w) << nSeats << '|' << setw(sm_w) << class_ << "|\n";
}

void User::PrintInFoForUser(const Admin& admin) const
{
	std::cout << "\nYour Informations are:\n\n";
	std::cout << "Username: " << username << "\n";
	std::cout << "password: " << password << "\n";
	if (travelScheduleId == -1)
	{
		std::cout << "\nYou have no reservations at the moment.\n\n";
	}
	else
	{
		std::cout << "\nYou have booked " << nSeats << " " << class_ << "-class seats for the following travel schedule: \n\n";
		admin.DisplayTravelSchedules(travelScheduleId);
		std::cout << "\n";
	}
}

const char * const User::GetPassword() const
{
	return password;
}

const char * const User::GetUsername() const
{
	return username;
}
