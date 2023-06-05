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
#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_
#include <iostream>
#include "Publication.h"
#include "Date.h"
#include "Lib.h"
using namespace std;
namespace sdds {
	class Book : public Publication {
	private:
		char* AuthorName;
	public:
		Book();
		~Book();
		Book(const Book& B);
		Book& operator=(const Book& B);
		char type() const;
		ostream& write(ostream& os) const;
		istream& read(istream& istr);
		void set(int member_id);
		operator bool() const;
	}; 
}


#endif // !SDDS_BOOK_H_
