#pragma once
#include <iostream>
#include <string>

class UserAccount
{
public:
	void GetInfo()
	{
		std::cout << "Enter username: ";
		std::cin >> username;
		std::cout << "Enter password: ";
		std::cin >> password;
	}
	void PrintInfo() const
	{
		std::cout << username << "\t" << password << "\n";
	}
	const std::string& GetName() const
	{
		return username;
	}
	const std::string& GetPassword() const
	{
		return password;
	}
private:
	static constexpr int maxSize = 30;
	char username[maxSize];
	std::string password[maxSize];
};