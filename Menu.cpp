/*
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Version 2.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include <string.h>
using namespace std;
using namespace sdds;

MenuItem::MenuItem() {
	itemName = nullptr;

}
MenuItem::MenuItem(const char* name) {
	if (!name) { itemName = nullptr; }

	else
	{
		itemName = new char[strlen(name) + 1];
		strcpy(itemName, name);
	}
}
MenuItem::~MenuItem() { delete[] itemName; }

MenuItem::operator bool() const { return (itemName != nullptr); }
MenuItem::operator const char* () const { return itemName; }
ostream& MenuItem::display(std::ostream& os)const {
	os << itemName;
	return os;
}

Menu::Menu() {
	menutracker = 0;
	for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		m_items[i] = nullptr;
	}
}
Menu::Menu(const char* title) : m_title(title) {
	menutracker = 0;
	for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		m_items[i] = nullptr;
	}
};

Menu::~Menu() {
	for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
	{
		delete m_items[i];
	}
}

std::ostream& Menu::displayTitle(std::ostream& os) {
	if (m_title != nullptr) {
		m_title.display(os);
		os << endl;
	}
	return os;
}

std::ostream& Menu::displayMenu(std::ostream& os) {
	if (m_title != nullptr)
	{
		displayTitle(os);
	}

	for (unsigned int i = 0; i < menutracker; i++)
	{
		os << " " << i + 1
			<< "- ";
		m_items[i]->display(os);
		os << endl;
	}
	os << " 0- Exit" << endl;
	os << "> ";

	return os;
}

int Menu::run() {

	int min_val = 0;
	int max_val = menutracker;
	int num_valid;
	bool flag = true;

	while (true) {
		if (flag) {
			displayMenu();
		}

		cin >> num_valid;
		while (std::cin.fail())
		{
			cout << "Invalid Selection, try again: ";
			cin.clear();
			cin.ignore(20, '\n');
			cin >> num_valid;
		}
		if (num_valid >= min_val && num_valid <= max_val)
		{
			flag = true;
			break;
		}
		else if (num_valid == 0) {
			break;
		}
		else {
			cout << "Invalid Selection, try again: ";
			flag = false;
		}
	}
	return num_valid;
}

int Menu::operator~() {
	return run();
}
Menu& Menu::operator<<(const char* menuitemConent) {
	if (menutracker < MAX_MENU_ITEMS) {
		m_items[menutracker] = new MenuItem(menuitemConent);
		menutracker++;
	}
	return *this;
}

const char* Menu::operator[](unsigned int index) const
{
	if (index > menutracker) {
		index %= menutracker;
	}
	return (const char*)m_items[index]->itemName;
}
Menu::operator int() { return menutracker; }

Menu::operator unsigned int() { return menutracker; }

Menu::operator bool() { return menutracker > 0; }

std::ostream& sdds::operator<<(std::ostream& os, Menu& menu)
{
	menu.displayTitle(os);
	return os;
}


void Menu::settitle(const char* title) {
	m_title.settitle(title);
}

void MenuItem::settitle(const char* title){
	strcpy(itemName, title);
}