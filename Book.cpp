/*
Final Project Milestone 5
Module: Book
Filename: Book.h
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Book.h"

using namespace std;

namespace sdds {
	Book::Book() : Publication() { AuthorName = nullptr; }
	Book::~Book() { delete[] AuthorName; }
	Book::Book(const Book& book) { *this = book; }
	Book& Book::operator=(const Book& B) {
		if (this != &B) {
			Publication::operator=(B);
			delete[]AuthorName;
			AuthorName = nullptr;
			if (B.AuthorName) {
				AuthorName = new char[strlen(B.AuthorName) + 1];
				strcpy(AuthorName, B.AuthorName);
			}
		}
		return *this;
	}
	char Book::type() const { return 'B'; }
	ostream& Book::write(ostream& os) const {
		Publication::write(os);
		if (conIO(os)) {
			char author[SDDS_AUTHOR_WIDTH + 1] = { 0 };
			os << " ";
			strncpy(author, AuthorName, SDDS_AUTHOR_WIDTH);
			os.width(SDDS_AUTHOR_WIDTH);
			os.fill(' ');
			os << left;
			os << author;
			os << " |";
		}
		else {
			os << "\t" << AuthorName;
		}
		return os;
	}
	istream& Book::read(istream& istr) {
		char author[256] = { 0 };
		Publication::read(istr);
		delete[] AuthorName;
		AuthorName = nullptr;
		if (conIO(istr))
		{
			istr.ignore();
			cout << "Author: ";
			istr.get(author, sizeof(author), '\n');
		}
		else
		{
			istr.ignore();
			istr.get(author, sizeof(author), '\n');
		}
		if (istr)
		{
			AuthorName = new char[strlen(author) + 1];
			strcpy(AuthorName, author);
		}
		return istr;
	}
	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}
	Book::operator bool() const {
		if (Publication::operator bool()) {
			if (AuthorName != nullptr) 	{ return true; }
		}
		return false;
	}
}