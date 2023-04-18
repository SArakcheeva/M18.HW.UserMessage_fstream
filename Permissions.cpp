#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


void demo_perms(fs::perms p)
{
	std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
		<< '\n';
}


/**
Права доступа к файлу
*/
void changePermissions(std::string file_name) {

	// Вывести информацию о доступе к файлу
	std::cout << "< " << file_name << " >" << std::endl;
	std::cout << "\tCreated file with permissions: ";
	demo_perms(fs::status(file_name).permissions());

	// Изменить права доступа:
	// файлы д.б. недоступны для других пользователей,
	// т.о. прочитать/записать информацию в файлы может только пользователь, который запускает программу
	fs::permissions(file_name,
		fs::perms::group_all | fs::perms::others_all,
		fs::perm_options::remove);

	// Вывести информацию о доступе к файлу после изменения прав
	std::cout << "\tAfter removing permissions:  ";
	demo_perms(fs::status(file_name).permissions());
}