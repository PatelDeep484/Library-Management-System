/*
Final Project Milestone 5
Module: Publication
Filename: Publication.cpp
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace sdds {
	Publication::Publication() {
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}

	Publication::~Publication() { delete[] m_title; }
	void Publication::set(int member_id) { m_membership = member_id; }
	void Publication::setRef(int value) { m_libRef = value; }
	void Publication::resetDate() { m_date = Date(); }
	char Publication::type()const { return 'P'; }
	bool Publication::onLoan()const { return m_membership != 0; }
	Date Publication::checkoutDate()const { return m_date; }
	bool Publication::operator==(const char* title)const { return strstr(m_title, title); }
	Publication::operator const char* ()const { return m_title; }
	int Publication::getRef()const { return m_libRef; }
	bool Publication::conIO(ios& io)const { return &io == &cin || &io == &cout; }
	Publication::operator bool() const { return (m_title != nullptr && m_shelfId[0] != '\0'); }

	ostream& Publication::write(ostream& os) const {
		char title[SDDS_TITLE_WIDTH + 1] = { 0 };
		strncpy(title, m_title, SDDS_TITLE_WIDTH);
		if (conIO(os)) {
			os << "| ";
			os.width(4);
			os << m_shelfId;
			os << " | ";
			os << left;
			os.width(30);
			os.fill('.');
			os << title;
			os << " | ";
			if (m_membership) { os << m_membership; }
			else { os << " N/A "; }
			os << " | ";
			os << m_date;
			os << " |";
		}
		else {
			os << type();
			os << "\t";
			os << m_libRef;
			os << "\t";
			os << m_shelfId;
			os << "\t";
			os << m_title;
			os << "\t";
			os << m_membership;
			os << "\t";
			os << m_date;
		}

		return os;
	}

	istream& Publication::read(istream& istr) {
		char title[256]{}, shelfID[SDDS_SHELF_ID_LEN + 1]{};
		int libRef = -1, membership = 0;
		Date date;
		int shelf_len = SDDS_SHELF_ID_LEN + 1;
		int title_len = 256;
		if (m_title) {
			delete[] m_title;
		}
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr.getline(shelfID, shelf_len);
			if (strlen(shelfID) != SDDS_SHELF_ID_LEN) { istr.setstate(ios::failbit); }
			cout << "Title: ";
			istr.getline(title, title_len);
			cout << "Date: ";
			istr >> date;
			if (!date) { istr.setstate(ios::failbit); }
		}
		else
		{
			istr >> libRef;
			istr.ignore();
			istr.getline(shelfID, shelf_len, '\t');
			istr.getline(title, title_len, '\t');
			istr >> membership;
			istr.ignore();
			istr >> date;
			if (!date) { istr.setstate(ios::failbit); }
		}
		if (istr) {
			m_libRef = libRef;
			m_membership = membership;
			strcpy(m_shelfId, shelfID);
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			m_date = date;
		}
		return istr;
	}

	Publication::Publication(const Publication& pb) { *this = pb; };
	Publication& Publication::operator=(const Publication& pub) {
		m_date = pub.m_date;
		m_membership = pub.m_membership;
		m_libRef = pub.m_libRef;
		strcpy(m_shelfId, pub.m_shelfId);
		if (m_title) {
			delete[] m_title;
			m_title = nullptr; }
		if (pub.m_title != nullptr) {
			m_title = new char[strlen(pub.m_title) + 1];
			strcpy(m_title, pub.m_title);
		} else { m_title = nullptr; }
		return *this;
	}
}