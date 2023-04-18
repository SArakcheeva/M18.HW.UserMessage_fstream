/**
\file User.h
\brief Класс содержит данные о пользователе
Класс инкапсулирует в себе параметры пользователя:
- Ник (имя) - по нику он будет известен другим пользователям
- Логин - имя по которому он будет заходить в чат
- Пароль
*/

#pragma once
#include <fstream>


class User {
	std::string _name;
	std::string _login;
	std::string _pass;

public:
	/**
	Конструктор по-умолчанию
	*/
	User();

	/**
	Параметризованный конструктор
	\param[in] name Ник пользователя
	\param[in] login Логин пользователя
	\param[in] pass Пароль пользователя
	*/
	User(std::string name, std::string login, std::string pass);

	/**
	\return Ник пользователя
	*/
	std::string getName() const;

	/**
	\return Логин пользователя
	*/
	std::string getLogin() const;

	friend std::fstream& operator >>(std::fstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);
};