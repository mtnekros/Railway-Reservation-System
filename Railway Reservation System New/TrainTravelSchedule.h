#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <ctime>

class TrainTravelSchedule
{
public:
	void SetTrainTravelID(int id);
	void GetInfoFromAdmin();
	void PrintInfo() const;
	void Serialize(std::ofstream& out);
	void Deserialize(std::ifstream& in);
	int GetId() const;
	static void PrintTitle();
	void AddSeats(int nSeats, char class_)
	{
		assert(class_ == 'f' || class_ == 's');
		if (class_ = 'f')
			availFirstSeats += nSeats;
		else
			availSecSeats += nSeats;
	}
public:
	static constexpr int maxSize = 30; // for the length of chars 
private:
	int travelScheduleId = 0;
	char trainName[maxSize];
	char boardingPt[maxSize];
	char destinationPt[maxSize];
	// first class seats info
	int totalFirstSeats; // total first class seats
	int availFirstSeats; // available first class seats
	double firstClassFare; // fare per seat
	// same info for second class seats
	int totalSecSeats;
	int availSecSeats;
	double secondClassFare;
	struct tm t = {}; // for time of departure of train. tm is a struct in ctime header
};

