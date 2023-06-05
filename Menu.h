/*
Final Project Milestone 5
Module: menu
Filename: Menu.h
Version 2.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
#include <string.h>

using namespace std;

namespace sdds {
		const unsigned int MAX_MENU_ITEMS = 20;
	class MenuItem {
	private:
		char* itemName;

		MenuItem();
		MenuItem(const char*);
		void settitle(const char*);
		~MenuItem();
		MenuItem(const MenuItem& source) = delete;
		MenuItem& operator=(const MenuItem& source) = delete;
		operator bool() const;
		operator const char* () const;

		std::ostream& display(std::ostream& os = std::cout)const;
		friend class Menu;
	};



	class Menu {
	public:
		MenuItem m_title;
		MenuItem* m_items[MAX_MENU_ITEMS];
		unsigned int menutracker;

		Menu();
		Menu(const char*);
		Menu(const Menu& source) = delete;
		Menu& operator=(const Menu& source) = delete;
		std::ostream& displayTitle(std::ostream& os);
		std::ostream& displayMenu(std::ostream& os = std::cout);
		~Menu();
		int run();
		int operator~();
		operator int();
		operator unsigned int();
		operator bool();
		Menu& operator<<(const char* menuitemConent);
		const char* operator[](unsigned int index) const;
		void settitle(const char*);

	};
	std::ostream& operator<<(std::ostream& os, Menu& menu);

}



#endif