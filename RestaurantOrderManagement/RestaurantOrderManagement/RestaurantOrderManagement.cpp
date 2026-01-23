#include "MainMenu.h"
#pragma once
int main()
{
    bool logging_screen = true;
	do
	{
		char choice_logging_screen;
		loginScreen();
		std::cout << "Please enter your choice: "; std::cin >> choice_logging_screen;
		if (choice_logging_screen == '1')
		{
			showMenuScreen();
		}

		else if (choice_logging_screen == '2')
		{
			std::string username; std::string password;
			std::cout << "Staff ID:"; std::cin >> username;

		}











		else if (choice_logging_screen == '3')
		{
			logging_screen = false;
		}
		else std::cout << "Wrong choice, please enter from (1-3)"<<std::endl;
		
	} while (logging_screen == true);
	return 0;
}
