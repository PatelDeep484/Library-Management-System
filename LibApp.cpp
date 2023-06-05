/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "LibApp.h"
#include <string.h>
#include "Book.h"
#include <fstream>
#include <cstring>
#include "Menu.h"
using namespace std;
namespace sdds {

	LibApp::LibApp(const char* filename) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), Pub_type("Choose the type of publication:") {
		strcpy(Fname, filename);
		m_changed = false;
		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";
		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";
		Pub_type << "Book"
			<< "Publication";
		load();
	}
	bool LibApp::confirm(const char* message) {
		Menu m1(message);
		m1 << "Yes";
		if (m1.run()) { return true; }
		else { return false; }
	}
	void LibApp::load() {
		cout << "Loading Data" << endl;

		ifstream infile(Fname);
		char info{};
		for (int i = 0; infile && i < SDDS_LIBRARY_CAPACITY; i++) {
			infile >> info;
			if (infile) {
				if (info == 'P') { PPA[i] = new Publication; }
				else if (info == 'B') { PPA[i] = new Book; }
			}
			if (PPA[i]) {
				infile >> *PPA[i];
				if (*PPA[NOLP]) { NOLP += 1; }
			}
		}
		if (NOLP) { LLRN = PPA[NOLP - 1]->getRef(); }
	}
	void LibApp::save() {
		cout << "Saving Data" << endl;
		ofstream onfile(Fname);
		for (int i = 0; i < NOLP; i++)
		{
			if (PPA[i]->getRef() != 0) {
				onfile << *PPA[i] << endl;
			}
		}
	}
	int LibApp::search(int search) {
		PublicationSelector PS("Select one of the following found matches:", SDDS_AUTHOR_WIDTH);
		int userPubType = 0;
		char title[256]{};
		int libRef{};
		do
		{
			userPubType = Pub_type.run();
			if (userPubType == 0) { break; }
			cin.ignore(1000, '\n');
			cout << "Publication Title: ";
			cin.getline(title, 256);
			if (search == 1) {
				if (userPubType == 1) {
					for (int i = 0; i < NOLP; i++) {
						if (PPA[i]->type() == 'B' && PPA[i]->getRef() && PPA[i]->operator==(title)) {
							PS << PPA[i];
						}

					}
				}
				else if (userPubType == 2) {
					for (int i = 0; i < NOLP; i++) {
						if (PPA[i]->type() == 'P' && PPA[i]->getRef() && PPA[i]->operator==(title)) {
							PS << PPA[i];
						};
					}
				}
			}
			else if (search == 2) {
				if (userPubType == 1) {
					for (int i = 0; i < NOLP; i++) {
						if (!PPA[i]->onLoan() && PPA[i]->type() == 'B' && PPA[i]->getRef() && PPA[i]->operator==(title)) {
							PS << PPA[i];
						}
					}
				}
				else if (userPubType == 2) {
					for (int i = 0; i < NOLP; i++) {

						if (!PPA[i]->onLoan() && PPA[i]->type() == 'P' && PPA[i]->getRef() && PPA[i]->operator==(title)) {
							PS << PPA[i];
						};
					}
				}
			}
			else if (search == 3) {
				if (userPubType == 1) {
					for (int i = 0; i < NOLP; i++) {
						if (PPA[i]->onLoan() && PPA[i]->type() == 'B' && PPA[i]->getRef() && PPA[i]->operator==(title)) { 
							PS << PPA[i];
						}
					}
				}
				else if (userPubType == 2) {
					for (int i = 0; i < NOLP; i++) {
						if (PPA[i]->onLoan() && PPA[i]->type() == 'P' && PPA[i]->getRef() && PPA[i]->operator==(title)) {
							PS << PPA[i];
						};
					}
				}
			}

			if (userPubType != 0 && PS) {
				PS.sort();
				libRef = PS.run();

				if (libRef > 0)
				{
					cout << *getPub(libRef) << endl;
				}

				if (libRef == 0) {
					cout << "Aborted!" << endl;
				}

			}
			else
			{
				cout << "No matches found!" << endl;
			}

		} while (0);

		return libRef;
	};
	LibApp::~LibApp() {
		for (int i = 0; i < NOLP; i++) { 
			delete PPA[i];
		}
	};
	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		int libref = search(3);
		if (libref && confirm("Return Publication?"))
		{
			Publication* P = getPub(libref);
			int days = Date() - P->checkoutDate();
			if (days > SDDS_MAX_LOAN_DAYS)
			{
				int exceedigDays = days - SDDS_MAX_LOAN_DAYS;
				double penalty = exceedigDays * 0.50;
				cout << "Please pay $";
				cout << fixed;
				cout.precision(2);
				cout << penalty;
				cout << " penalty for being ";
				cout << exceedigDays;
				cout << " days late!" << endl;
			}
			P->set(0);
			m_changed = true;
			cout << "Publication returned" << endl;
		}
	}
	void LibApp::newPublication() {
		if (NOLP == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
 		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			Publication* PubOrBook{};
			int type = Pub_type.run();
			do {
				if (type == 0) {
					delete PubOrBook;
					cout << "Aborted!" << endl;
					break;
				}
				if (type == 1) { PubOrBook = new Book; }
				else if (type == 2) { PubOrBook = new Publication; }
				cin.ignore(1000, '\n');
				cin >> *PubOrBook;
				if (cin.fail()) {
					cin.ignore(1000, '\n');
					cout << "Aborted!" << endl;
					break;
				}
				if (confirm("Add this publication to the library?")) {
					if (*PubOrBook)
					{
						LLRN++;
						PPA[NOLP] = PubOrBook;
						NOLP++;
						PubOrBook->setRef(LLRN);
						m_changed = true;
						cout << "Publication added" << endl;
					}
					else
					{
						cout << "Failed to add publication!" << endl;
						delete PubOrBook;
					}
				}
				else {
					delete PubOrBook;
					cout << "Aborted!" << endl;
					break;
				}

			} while (0);
		}
	};
	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int libRef = search(1);
		if (libRef && confirm("Remove this publication from the library?")) {
			getPub(libRef)->setRef(0);
			m_changed = true;
			cout << "Publication removed" << endl;
		}
	}
	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int libref = search(2);
		if (libref && confirm("Check out publication?")) {
			cout << "Enter Membership number: ";
			int membership_num;
			while (true)
			{
				cin >> membership_num;
				if (cin.fail() || membership_num < 10000 || membership_num > 99999)
				{
					cout << "Invalid membership number, try again: ";
					cin.ignore(1000, '\n');
				}
				else
				{
					break;
				}
			}
			getPub(libref)->set(membership_num);
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
	}
	void LibApp::run() {
		int displaymenu;
		do
		{
			displaymenu = m_mainMenu.run();
			if (displaymenu == 1)
			{
				newPublication();
			}
			else if (displaymenu == 2)
			{
				removePublication();
			}
			else if (displaymenu == 3)
			{
				checkOutPub();
			}
			else if (displaymenu == 4)
			{
				returnPub();
			}
			else if (displaymenu == 0)
			{
				if (m_changed == true)
				{
					int exitmenu = m_exitMenu.run();
					if (exitmenu == 1)
					{
						save();
					}
					else if (exitmenu == 2)
					{
						displaymenu = 21;
					}
					else if (exitmenu == 0)
					{
						if (confirm("This will discard all the changes are you sure?")) {
							m_changed = false;
						}
					}
				}
			}
			cout << endl;
		} while (displaymenu != 0);
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}
	Publication* LibApp::getPub(int libRef) {
		for (int i = 0; i < NOLP; i++)
		{
			if (PPA[i]->getRef() == libRef) {
				return PPA[i];
			}
		}
		return nullptr;
	}
}