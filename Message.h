/**
\file Message.h
\brief Класс содержит данные о сообщениях пользователя
Класс инкапсулирует в себе параметры пользователя:
- Ник (имя) - по нику он будет известен другим пользователям
- Логин - имя по которому он будет заходить в чат
- Пароль
*/

#pragma once
#include <fstream>

class Message {
	std::string _text;
	std::string _sender;
	std::string _receiver;

public:
	/**
	Конструктор по-умолчанию
	*/
	Message();

	/**
	Параметризованный конструктор
	\param[in] text Текст сообщения
	\param[in] sender Ник пользователя от которого сообщение
	\param[in] receiver Ник пользователя кому адресовано сообщение
	*/
	Message(std::string text, std::string sender, std::string receiver);

	/**
	\return Текст сообщения
	*/
	std::string getText() const;

	/**
	\return Ник пользователя
	*/
	std::string getSender() const;

	/**
	\return Ник пользователя
	*/
	std::string getReceiver() const;

	friend std::fstream& operator >>(std::fstream& is, Message& mess);
	friend std::ostream& operator <<(std::ostream& os, const Message& mess);
};