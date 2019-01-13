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
	void SetTrainTravelID(int id)
	{
		travelScheduleId = id;
	}
	void GetInfo()
	{
		std::cout << "Enter the details of the route\n";
		std::cout << "Train name:";
		std::cin >> trainName;
		std::cout << "Boarding point:";
		std::cin >> (boardingPt);
		std::cout << "Destination pt:";
		std::cin >> (destinationPt);
		std::cout << "No of seats in first class & fare per ticket:";
		std::cin >> totalFirstSeats >> firstClassFare;
		std::cout << "No of seats in second class & fare per ticket:";
		std::cin >> totalSecSeats >> secondClassFare;
		availFirstSeats = totalFirstSeats; // becoz all seats available at first
		availSecSeats = totalSecSeats;
		std::cout << "Date of travel(day month year):";
		std::cin >> t.tm_mday >> t.tm_mon >> t.tm_year;
		t.tm_year -= 1900; // tm_year counts from 1900 
		std::cout << "Time of travel(hour min in 24 hour format)";
		std::cin >> t.tm_hour >> t.tm_min;
		std::cout << std::endl;
	}
	void PrintInfo() const 
	{
		using namespace std;
		// for convertin struct tm t to string
		char timeStr[30];
		asctime_s(timeStr,sizeof(timeStr),&t);
		//printing details
		const int sm_w = 10;
		const int bg_w = 15;
		const int ex_bg_w = 28;
		cout << '|' << setw(sm_w) << travelScheduleId << '|' << setw(bg_w) << trainName << '|' << setw(bg_w) << boardingPt << '|';
		cout << setw(bg_w) << destinationPt << '|' << setw(sm_w) << availFirstSeats << '|' << setw(sm_w) << firstClassFare << '|';
		cout << setw(sm_w) << availSecSeats << '|' << setw(sm_w) << secondClassFare << '|' << setw(ex_bg_w) << timeStr;
	}
	void Serialize(std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	void Deserialize(std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	int GetId() const
	{
		return travelScheduleId;
	}
	static void PrintTitle() // to print the titles of the table when displaying train info
	{
		using namespace std;
		const int sm_w = 10;
		const int bg_w = 15;
		const int ex_bg_w = 28;
		// border
		cout << "__________________________________________________________________________________________________________________________________\n";

		// first line
		cout << '|' << setw(sm_w) << "Id" << '|' << setw(bg_w) << "Train Name" << '|' << setw(bg_w) << "Boarding" << '|';
		cout << setw(bg_w) << "Destination" << '|' << setw(sm_w) << "Available" << '|' << setw(sm_w) << "First" << '|';
		cout << setw(sm_w) << "Available" << '|' << setw(sm_w) << "Second" << '|' << setw(ex_bg_w) << "Time Of|\n";
		// second line
		cout << '|' << setw(sm_w) << " " << '|' << setw(bg_w) << "Point" << '|' << setw(bg_w) << "Point" << '|';
		cout << setw(bg_w) << "Point" << '|' << setw(sm_w) << "FirstSeats" << '|' << setw(sm_w) << "Class Fare" << '|';
		cout << setw(sm_w) << "SecSeats" << '|' << setw(sm_w) << "ClassFare" << '|' << setw(ex_bg_w) << "Departure|\n";
		cout << "__________________________________________________________________________________________________________________________________\n";

	}
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

