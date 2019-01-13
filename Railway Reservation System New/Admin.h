#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "UserAccount.h"
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
			out.write(reinterpret_cast<char*>(&nTrains), sizeof(nTrains)); 
			out.close();
		}
		else // if there is data in the file
		{
			in.seekg(0);
			// first data in the file is number of current trains
			in.read(reinterpret_cast<char*>(&nTrains), sizeof(nTrains));
			// load the train data from the file stream to train object
			for (int i = 0; i < nTrains; i++)
			{
				trains[i].Deserialize(in);
			}
		}
		in.close();
	}
	~Admin()
	{
		std::ofstream out(trainInfoFile,std::ios::binary);
		out.write(reinterpret_cast<char*>(&nTrains), sizeof(nTrains));
		for (int i = 0; i < nTrains; i++)
		{
			trains[i].Serialize(out);
		}
	}
	void AddTrain() 
	{
		trains[nTrains++].GetInfo();
	}
	void RemoveTrain()
	{
	}
	void DisplayTrains() const
	{
		for (int i = 0; i < nTrains; i++)
		{
			trains[i].PrintInfo();
		}
	}
	void DisplayUserAccounts() {}
private:
	std::string password = "password";
	std::string trainInfoFile = "trainsInfo.txt";
	std::string userInfoFile = "usersInfo.txt";
	
	constexpr static int maxTrains = 25; // max no of trains
	int nTrains = 0; // current no of train
	Train trains[maxTrains];
	
	constexpr static int maxUsers = 100;
	int nUsers = 0; // no of current users
	UserAccount users[maxUsers];
};