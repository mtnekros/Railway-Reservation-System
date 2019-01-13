#pragma once
#include <string>
#include <iostream>
#include <ctime>

class Train
{
public:
	void GetInfo()
	{
		std::cout << "Enter the details of the route\n";
		std::cout << "Train no:";
		std::cin >> trainNo;
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
		std::cout << trainNo << "\t" << trainName << "\t" << boardingPt << "\t" << destinationPt << "\t" << nFirstClassSeats << "\t";
		std::cout << firstClassFare << "\t" << nSecondClassSeats << "\t" << secondClassFare << "\t" <<timeStr;
	}
private:
	static constexpr int maxSize = 30; // for the length of chars 

	int trainNo;
	char trainName[maxSize];
	char boardingPt[maxSize];
	char destinationPt[maxSize];
	int nFirstClassSeats;
	double firstClassFare;
	int nSecondClassSeats;
	double secondClassFare;
	struct tm t = {}; // for time of departure of train. tm is a struct in ctime header
};

// just in case
/*
{
	struct tm t = { };
	t.tm_year = 2018 - 1900;
	t.tm_mon = 11;
	t.tm_mday = 12;
	char t_charRep[26];
	asctime_s(t_charRep,sizeof(t_charRep),&t);
	std::cout << t_charRep;
}
*/