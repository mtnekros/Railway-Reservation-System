#pragma once
#include <iostream>
#include <fstream>

class User
{
public:
	void SetUsername(const char* const in_password);
	void SetPassword(const char* const in_password);
	void MakeReservation(class Admin& admin);
	void CancelReservation(class Admin& admin);
	void Deserialize(std::ifstream& in);
	void Serialize(std::ofstream& out) const;
	static void PrintTitles();
	void PrintInfoForAdmin() const;
	void PrintInFoForUser(const class Admin& admin) const;
	const char* const GetUsername() const;
	const char* const GetPassword() const;
private:
	constexpr static int maxSize = 30;
	char username[maxSize];
	char password[maxSize];
	int travelScheduleId = -1;
	int nSeats = 0;
	char class_ = '0';
};