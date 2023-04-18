#include "User.h"
#include <fstream>


User::User() = default;


User::User(std::string name, std::string login, std::string pass)
{
	_name = name;
	_login = login;
	_pass = pass;
}


std::string User::getName() const
{
	return _name;
}



std::string User::getLogin() const
{
	return _login;
}


std::fstream& operator >> (std::fstream& is, User& user)
{
	is >> user._name;
	is >> user._login;
	is >> user._pass;
	return is;
}


std::ostream& operator << (std::ostream& os, const User& user)
{
	os << user._name;
	os << ' ';
	os << user._login;
	os << ' ';
	os << user._pass;

	return os;
}