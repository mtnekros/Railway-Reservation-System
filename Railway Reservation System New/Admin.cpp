#include "Admin.h"
#include <string>

Admin::Admin()
{
	// load  data from the file if there is data in the file
	LoadScheduleData();
	LoadUserData();
}

Admin::~Admin()
{
	// saving train data
	{
		std::ofstream out(trainInfoFile, std::ios::binary);
		int nSchedules = schedules.size();
		out.write(reinterpret_cast<char*>(&nSchedules), sizeof(nSchedules));
		for (int i = 0; i < nSchedules; i++)
		{
			schedules[i].Serialize(out);
		}
	}
	// save user data
	{
		std::ofstream out(userInfoFile, std::ios::binary);
		int nUsers = users.size();
		out.write(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
		for (int i = 0; i < nUsers; i++)
		{
			users[i].Serialize(out);
		}
	}
}

void Admin::AddTravelSchedule()
{
	int nSchedules = schedules.size();
	int newID = (nSchedules == 0) ? 0 : schedules[nSchedules - 1].GetId() + 1;
	TrainTravelSchedule temp;
	temp.SetTrainTravelID(newID);
	temp.GetInfoFromAdmin();
	schedules.push_back(temp);
}

void Admin::AddUser()
{
	char username[30];
	char password[30];
	bool alreadyTaken = false;
	do
	{
		std::cout << "Enter your username: ";
		std::cin >> username;
		if (alreadyTaken = SearchUser(username) != -1)
			std::cout << username << " is already taken! Try again.\n\n";

	} while (alreadyTaken); // repeat asking username until username is not unique

	const int nUsers = users.size();
	users.emplace_back();
	users[nUsers].SetUsername(username);
	std::cout << "Enter your password: ";
	std::cin >> password;
	users[nUsers].SetPassword(password);
	std::cout << "\n";
}

void Admin::RemoveTravelSchedule()
{
	std::cout << "The information about the travel are: \n\n";
	DisplayTravelSchedules();
	int cancelId;
	std::cout << "\nEnter the id of the travel schedule you want to cancel: ";
	std::cin >> cancelId;
	// loop througth the schedules to find schedule to be cancelled
	int i = SearchSchedule(cancelId);
	schedules.erase(schedules.begin() + i);
}

void Admin::DisplayTravelSchedules() const
{
	TrainTravelSchedule::PrintTitle();
	for (int i = 0; i < int(schedules.size()); i++)
	{
		schedules[i].PrintInfo();
	}
	std::cout << "\n";
}

void Admin::DisplayTravelSchedules(int id) const
{
	int i = SearchSchedule(id);
	assert(i>=0);
	TrainTravelSchedule::PrintTitle();
	schedules[i].PrintInfo();
	std::cout << std::endl;
}

TrainTravelSchedule& Admin::GetSchedule(int index) 
{
	assert(index >= 0);
	assert(index < int(schedules.size()));
	return schedules[index];
}

void Admin::DisplayUserAccounts() const
{
	User::PrintTitles();
	for (int i = 0; i < int(users.size()); i++)
	{
		users[i].PrintInfoForAdmin();
	}
	std::cout << "\n";
}

// function to search id and index, return -1 if not found
int Admin::SearchSchedule(int id) const
{
	for (int i = 0; i < int(schedules.size()); i++)
	{
		if (schedules[i].GetId() == id)
			return i;
	}
	return -1;
}

int Admin::SearchUser(const std::string & username) const
{
	for (int i = 0; i < int(users.size()); i++)
	{
		if (std::strcmp(users[i].GetUsername(), username.c_str()) == 0)
			return i;
	}
	return -1;
}

User& Admin::GetUser(int index)
{
	assert(index >= 0);
	assert(index < int(users.size()));
	return users[index];
}

void Admin::AddAvailSeatsFor(int id, int nSeats, char class_)
{
	int i = SearchSchedule(id);
	schedules[i].AddSeats(nSeats, class_);
}

void Admin::LoadScheduleData()
{
	std::ifstream in(trainInfoFile, std::ios::binary);
	if (in.get() == -1) // if the file's not there or is empty
	{
		std::cout << "No travel schedule data\n";
		std::ofstream out(trainInfoFile, std::ios::binary);
		int nSchedules = schedules.size();
		out.write(reinterpret_cast<char*>(&nSchedules), sizeof(nSchedules));
		out.close();
	}
	else // if there is data in the file
	{
		in.seekg(0);
		// first data in the file is number of train schedules
		int nSchedules;
		in.read(reinterpret_cast<char*>(&nSchedules), sizeof(nSchedules));
		schedules.resize(nSchedules);
		// load the train data from the file stream to train object
		for (int i = 0; i < nSchedules; i++)
		{
			schedules[i].Deserialize(in);
		}
	}
	in.close();
}

void Admin::LoadUserData()
{
	std::ifstream in(userInfoFile, std::ios::binary);
	if (in.get() == -1) // if the file's not there or is empty
	{
		std::cout << "No user data\n";
		std::ofstream out(userInfoFile, std::ios::binary);
		int nUsers = users.size();
		out.write(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
		out.close();
	}
	else // if there is data in the file
	{
		in.seekg(0);
		// first data in the file is number of train schedules
		int nUsers;
		in.read(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
		users.resize(nUsers);
		// load the train data from the file stream to train object
		for (int i = 0; i < nUsers; i++)
		{
			users[i].Deserialize(in);
		}
	}
	in.close();
}
