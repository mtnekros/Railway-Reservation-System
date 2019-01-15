#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TrainTravelSchedule.h"
#include "User.h"

class Admin
{
public:
	Admin();
	~Admin();
	void AddTravelSchedule();
	void RemoveTravelSchedule();
	void DisplayTravelSchedules() const;
	void DisplayTravelSchedules(int id) const;
	TrainTravelSchedule& GetSchedule(int index);
	// function to search id and index, return -1 if not found
	int SearchSchedule(int id) const;

	void AddUser();
	void DisplayUserAccounts() const;
	int SearchUser(const std::string& username) const;
	User& GetUser(int index);
	void AddAvailSeatsFor(int id, int nSeats, char class_);
private:
	void LoadScheduleData();
	void LoadUserData();
private:
	std::string trainInfoFile = "trainsInfo.txt";
	std::string userInfoFile = "usersInfo.txt";
	
	std::vector<TrainTravelSchedule> schedules;
	std::vector<User> users;
};