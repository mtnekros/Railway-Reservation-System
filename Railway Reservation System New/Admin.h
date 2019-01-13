#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Train.h"

class Admin
{
public:
	Admin()
	{
		// load data from the file if there is data in the file
		std::ifstream in(trainInfoFile, std::ios::binary);
		if (in.get() == -1) // if the file's not there or is empty
		{
			std::cout << "No data";
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
	~Admin()
	{
		std::ofstream out(trainInfoFile,std::ios::binary);
		int nSchedules = schedules.size();
		out.write(reinterpret_cast<char*>(&nSchedules), sizeof(nSchedules));
		for (int i = 0; i < nSchedules; i++)
		{
			schedules[i].Serialize(out);
		}
		out.close();
	}
	void AddTravelSchedule() 
	{
		int nSchedules = schedules.size();
		int newID = (nSchedules==0) ? 0 : schedules[nSchedules - 1].GetId() + 1;
		schedules.emplace_back();
		schedules[nSchedules].SetTrainTravelID( newID );
		schedules[nSchedules].GetInfo();
	}
	void RemoveTravelSchedule()
	{
		DisplayTravelSchedules();
		int cancelId;
		std::cout << "\nEnter the id of the travel schedule you want to cancel: ";
		std::cin >> cancelId;
		// loop througth the schedules to find schedule to be cancelled
		int i = SearchSchedule(cancelId);
		schedules.erase(schedules.begin()+i);
	}
	void DisplayTravelSchedules() const
	{
		for (int i = 0; i < int(schedules.size()); i++)
		{
			schedules[i].PrintInfo();
		}
	}
	void DisplayUserAccounts() 
	{
	}
	// function to search id and index, return -1 if not found
	int SearchSchedule(int id)
	{
		for (int i = 0; i < int(schedules.size()); i++)
		{
			if (schedules[i].GetId() == id)
				return i;
		}
		return -1;
	}
	void DeductAvailSeatsFor(int id, int nSeats, char class_)
	{
		int i = SearchSchedule(id);
		schedules[i].DeductSeats(nSeats, class_);
	}
private:
	std::string password = "password";
	std::string trainInfoFile = "trainsInfo.txt";
	std::string userInfoFile = "usersInfo.txt";
	
	std::vector<TrainTravelSchedule> schedules;
};