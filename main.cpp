/* Программа должна считывать из файла при загрузке и записывать в файл
 * состояния объектов классов User и Message(для каждого класса свой файл).
 * Файлы были недоступны для других пользователей, т.е. чтобы прочитать/записать информацию в файлы
 * мог бы только пользователь, который запускает программу.
 */
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "User.h"
#include "Message.h"


namespace {
	//База зарегистрированных пользователей
	//где: string - id пользователя(login); User - структура с данными пользователя (ник-логин-пароль)
	std::map <std::string, User> all_users;

	//База сообщений пользователей друг другу
	std::list<Message> all_messages;
}


void infoAboutUsers() {

	// Попытка открыть файл при загрузке программы - вывести данные из файла, если файл существует
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	if (user_file) {
		// Установить позицию для чтения в начало файла
		user_file.seekg(0, std::ios_base::beg);

		// Считываем данные из файла
		while (true) {
			User user;
			user_file >> user;
			if (user_file.eof()) {
				break;
			}
			std::pair<std::string, User> new_pair = std::make_pair(user.getLogin(), user);
			all_users.insert(new_pair);
		}

		// Вывести информацию об объекте на консоль.
		std::cout << "All users < Nik Login Password >:" << std::endl;
		for (auto user_ : all_users) {
			std::cout << "\t" << user_.second << std::endl;
		}
	}

	// -----------------------------------------------------------------------
	// Создаем новый поток для добавления нового пользователя
	user_file = std::fstream("users.txt", std::ios::in | std::ios::out);

	// Если файл отсутствует, его надо создать (параметр ios::trunc)
	if(!user_file) {
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
	}
	if (user_file) {
		// Добавить нового пользователя
		std::cout << "Add new user:" << std::endl;
		std::string name;
		std::string login;
		std::string password;

		while (true) {
			std::cout << "\tLogin: ";
			std::getline(std::cin >> std::ws, login); //Функция ввода ws использует пробелы из входного потока
			if (all_users.find(login) != all_users.end()) {
				std::cout << "Login exists! Try again" << std::endl;
				continue;
			}
			else {
				break;
			}
		}
		
		std::cout << "\tPassword: ";
		std::getline(std::cin >> std::ws, password);
		std::cout << "\tNik: ";
		std::getline(std::cin >> std::ws, name);
		std::cout << "User added" << std::endl;

		// Добавим в базу пользователей и запишем в файл
		User new_user(name, login, password);
		std::pair<std::string, User> new_pair2 = std::make_pair(new_user.getLogin(), new_user);
		all_users.insert(new_pair2);

		// Установить позицию для записи в конец файла
		user_file.seekp(0, std::ios_base::end);

		// Запишем данные по user в файл
		user_file << new_user << std::endl;
	}
	else {
		std::cout << "Could not open file users.txt !" << '\n';
	}

	std::cout << "---------------------------------------------------" << std::endl;
}


void infoAboutMessages() {

	// Попытка открыть файл
	std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
	if (message_file) {
		// Сначала надо установить позицию для чтения в начало файла
		message_file.seekg(0, std::ios_base::beg);

		// Считываем данные из файла
		while (true) {
			Message mess;
			message_file >> mess;
			if (message_file.eof()) {
				break;
			}
			all_messages.push_back(mess);
		}

		// Вывести информацию об объекте на консоль.
		std::cout << "All message:" << std::endl;
		for (auto mess_ : all_messages) {
			std::cout << "\tFrom " << mess_.getSender()
				<< " to " << mess_.getReceiver() << ": "
				<< mess_.getText() << std::endl;
		}
	}

	// -----------------------------------------------------------------------
	// Создаем новый поток для добавления нового сообщения
	message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);

	// Если файл отсутствует, его надо создать (параметр ios::trunc)
	if (!message_file) {
		message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
	}

	if (message_file) {
		// Добавить новое сообщение
		std::cout << "Create new message:" << std::endl;
		std::string text;
		std::string sender;
		std::string receiver;

		bool is_find = false;
		while (is_find == false) {
			std::cout << "\tSender's name: ";
			std::getline(std::cin >> std::ws, sender); //Функция ввода ws использует пробелы из входного потока

			for (const auto& user : all_users) {
				if (user.second.getName() == sender) {
					is_find = true;
					break;
				}
			}
			if (is_find == false) {
				std::cout << "User not found. Try again" << std::endl;
			}
		}

		is_find = false;
		while (is_find == false) {
			std::cout << "\tReceiver's name: ";
			std::getline(std::cin >> std::ws, receiver);
			for (const auto& user : all_users) {
				if (user.second.getName() == receiver) {
					is_find = true;
					break;
				}
			}
			if (is_find == false) {
				std::cout << "User not found. Try again" << std::endl;
			}
		}

		std::cout << "\tMessage: ";
		std::getline(std::cin >> std::ws, text);
		//Текст введён
		if (!text.empty()) {
			//Создать сообщение
			Message new_message(text, sender, receiver);

			//Поместить в базу сообщений
			all_messages.push_back(new_message);
			std::cout << "Message has been sent" << std::endl;

			// Запишем в файл:
			// Сначала надо установить позицию для записи в конец файла
			message_file.seekp(0, std::ios_base::end);

			// Запишем данные по message в файл
			message_file << new_message << std::endl;
		}
		//Текст не введён
		else {
			std::cout << "The message hasn't been sent (text is missing)\n";
		}
	}
	else {
		std::cout << "Could not open file messages.txt !" << '\n';
	}

	std::cout << "---------------------------------------------------" << std::endl;
}


// изменение прав доступа файла
void changePermissions(std::string file_name);


int main() {

	infoAboutUsers();
	infoAboutMessages();

	changePermissions("users.txt");
	changePermissions("messages.txt");

	return 0;
}