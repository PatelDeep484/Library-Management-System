/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.h
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_LIBAPP_H__
#define SDDS_LIBAPP_H__
#include <iostream>
#include <string.h>
#include "Menu.h"
#include "Publication.h"
#include "PublicationSelector.h"
#include "Book.h"
#include "Lib.h"
using namespace std;

namespace sdds {
	class LibApp {
	private:

		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;

		char Fname[256];
		Publication* PPA[SDDS_LIBRARY_CAPACITY]{};
		
		int NOLP{};
		int LLRN{};

		Menu Pub_type;

		bool confirm(const char* message);
		void load();
		void save(); 
		int search(int search);
		void returnPub();
		void newPublication();
		void removePublication();
		void checkOutPub();
	public:
		LibApp(const char* filename);
		~LibApp();
		void run();

		Publication* getPub(int libRef);
	};
}




#endif