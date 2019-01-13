#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class TrainTravelSchedule
{
public:
	void SetTrainTravelID(int id)
	{
		trainTravelId = id;
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
		std::cin >> nFirstClassSeats >> firstClassFare;
		std::cout << "No of seats in second class & fare per ticket:";
		std::cin >> nSecondClassSeats >> secondClassFare;

		std::cout << "Date of travel(day month year):";
		std::cin >> t.tm_mday >> t.tm_mon >> t.tm_year;
		std::cout << "Time of travel(hour min in 24 hour format)";
		std::cin >> t.tm_hour >> t.tm_min;
	}
	static void PrintTitle() // to print the titles of the table when displaying train info
	{
		std::cout << "|Trn No\t|Trn Name\t|Boarding Pt\t|Dest Pt\t|1st Cls Seats\t";
		std::cout << "|Fare\t|2nd Cls Seats\t|Fare\t|Depart time\t|\n";
	}
	void PrintInfo() const 
	{
		// for convertin struct tm t to string
		char timeStr[26];
		asctime_s(timeStr,sizeof(timeStr),&t); 
		//printing details
		std::cout << trainTravelId << "\t" << trainName << "\t" << boardingPt << "\t" << destinationPt << "\t" << nFirstClassSeats << "\t";
		std::cout << firstClassFare << "\t" << nSecondClassSeats << "\t" << secondClassFare << "\t" <<timeStr;
	}
	void Serialize(std::ofstream& out)
	{
		out.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	void Deserialize(std::ifstream& in)
	{
		in.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	int GetId()
	{
		return trainTravelId;
	}
private:
	static constexpr int maxSize = 30; // for the length of chars 

	int trainTravelId = 0;
	char trainName[maxSize];
	char boardingPt[maxSize];
	char destinationPt[maxSize];
	int nFirstClassSeats;
	double firstClassFare;
	int nSecondClassSeats;
	double secondClassFare;
	struct tm t = {}; // for time of departure of train. tm is a struct in ctime header
};

