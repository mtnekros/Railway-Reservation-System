#include "TrainTravelSchedule.h"

void TrainTravelSchedule::SetTrainTravelID(int id)
{
	travelScheduleId = id;
}

void TrainTravelSchedule::GetInfoFromAdmin()
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

void TrainTravelSchedule::Serialize(std::ofstream & out)
{
	out.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void TrainTravelSchedule::Deserialize(std::ifstream & in)
{
	in.read(reinterpret_cast<char*>(this), sizeof(*this));
}

int TrainTravelSchedule::GetId() const
{
	return travelScheduleId;
}

int TrainTravelSchedule::GetAvailSeats(char class_) const
{
	assert(class_ == 'f' || class_ == 's');
	if (class_ == 'f')
		return availFirstSeats;
	else
		return availSecSeats;
}

void TrainTravelSchedule::PrintTitle() // to print the titles of the table when displaying train info
{
	using namespace std;
	const int sm_w = 10;
	const int bg_w = 15;
	const int ex_bg_w = 28;
	const std::string sm_wt = "----------";
	const std::string bg_wt = "---------------";
	const std::string ex_bg_wt = "----------------------------";
	// border
	cout << "+" << sm_wt << "+" << bg_wt << "+" << bg_wt << "+" << bg_wt << "+" << sm_wt << "+" << sm_wt << "+"
		<< sm_wt << "+" << sm_wt << "+" << ex_bg_wt << "+\n";

	// first line
	cout << '|' << setw(sm_w) << "Id" << '|' << setw(bg_w) << "Train Name" << '|' << setw(bg_w) << "Boarding" << '|'
		<< setw(bg_w) << "Destination" << '|' << setw(sm_w) << "Available" << '|' << setw(sm_w) << "First" << '|'
		<< setw(sm_w) << "Available" << '|' << setw(sm_w) << "Second" << '|' << setw(ex_bg_w) << "Time Of" <<"|\n";
	// second line
	cout << '|' << setw(sm_w) << " " << '|' << setw(bg_w) << "Point" << '|' << setw(bg_w) << "Point" << '|'
		<< setw(bg_w) << "Point" << '|' << setw(sm_w) << "FirstSeats" << '|' << setw(sm_w) << "Class Fare" << '|'
		<< setw(sm_w) << "SecSeats" << '|' << setw(sm_w) << "ClassFare" << '|' << setw(ex_bg_w) << "Departure" << "|\n";

	cout << "+" << sm_wt << "+" << bg_wt << "+" << bg_wt << "+" << bg_wt << "+" << sm_wt << "+" << sm_wt << "+"
		<< sm_wt << "+" << sm_wt << "+" << ex_bg_wt << "+\n";

}

void TrainTravelSchedule::PrintInfo() const
{
	using namespace std;
	// for convertin struct tm t to string
	char timeStr[30];
	asctime_s(timeStr, sizeof(timeStr), &t);
	timeStr[strlen(timeStr)-1] = 0;
	//printing details
	const int sm_w = 10;
	const int bg_w = 15;
	const int ex_bg_w = 28;
	cout << '|' << setw(sm_w) << travelScheduleId << '|' << setw(bg_w) << trainName << '|' << setw(bg_w) << boardingPt << '|';
	cout << setw(bg_w) << destinationPt << '|' << setw(sm_w) << availFirstSeats << '|' << setw(sm_w) << firstClassFare << '|';
	cout << setw(sm_w) << availSecSeats << '|' << setw(sm_w) << secondClassFare << '|' << setw(ex_bg_w) << timeStr << "|\n";
}

