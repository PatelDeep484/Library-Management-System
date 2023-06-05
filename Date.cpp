/*
Final Project Milestone 5
Module: Date
Filename: Date.cpp
Version 2.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;
#include "Date.h"
namespace sdds
{
    bool sdds_test = false;
    int sdds_year = 2022;
    int sdds_mon = 8;
    int sdds_day = 7;


    bool Date::validate()
    {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
        {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12)
        {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays())
        {
            errCode(DAY_ERROR);
        }
        return !bad();
    }

    bool Date::operator!()
    {
        return bad();
    }

    int Date::mdays() const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }
    int Date::systemYear()const {
        int theYear = sdds_year;
        if (!sdds_test) {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            theYear = lt.tm_year + 1900;
        }
        return theYear;
    }
    void Date::setToToday() {
        if (sdds_test) {
            m_day = sdds_day;
            m_mon = sdds_mon;
            m_year = sdds_year;
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            m_day = lt.tm_mday;
            m_mon = lt.tm_mon + 1;
            m_year = lt.tm_year + 1900;
        }
        errCode(NO_ERROR);
    }
    int Date::daysSince0001_1_1() const
    { // Rata Die day since 0001/01/01
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3)
        {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }
    Date::Date() : m_CUR_YEAR(systemYear())
    {
        setToToday();
    }
    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
    {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }
    const char* Date::dateStatus() const
    {
        return DATE_ERROR[errCode()];
    }
    int Date::currentYear() const
    {
        return m_CUR_YEAR;
    }
    void Date::errCode(int readErrorCode)
    {
        m_ErrorCode = readErrorCode;
    }
    int Date::errCode() const
    {
        return m_ErrorCode;
    }
    bool Date::bad() const
    {
        return m_ErrorCode != 0;
    }

    ostream& operator<<(ostream& os, const Date& RO)
    {
        return RO.write(os);
    }
    std::ostream& Date::write(std::ostream& os) const
    {
        int x = bad();
        if (x)	os << dateStatus();
        else {
            data(os);
        }

        return os;
    }
    std::ostream& Date::data(std::ostream& dp) const {
        dp << m_year << "/";
        dp << setfill('0');
        dp << setw(2);
        dp << right;
        dp << m_mon << "/";
        dp << setfill('0');
        dp << setw(2);
        dp << right << m_day;

        return dp;
    }
    

    istream& operator>>(istream& is, Date& RO)
    {
        return RO.read(is);
    }

    std::istream& Date::read(std::istream& is) {
        int y, m, d;
        errCode(NO_ERROR);

        is >> y;
        is.ignore();

        is >> m;
        is.ignore();

        is >> d;

        if (is) {
            m_year = y; m_mon = m; m_day = d;
            validate();
        }
        else {
            errCode(CIN_FAILED);
            is.clear();
        }
        return is;
    }
    int Date::getDays() const { return daysSince0001_1_1(); }
    Date::operator bool() const { return !bad(); }
    bool operator==(Date const& ls, Date const& rs)
    {
        return ls.getDays() == rs.getDays();
    }

    bool operator!=(Date const& ls, Date const& rs)
    {
        return ls.getDays() != rs.getDays();
    }

    bool operator>=(Date const& ls, Date const& rs)
    {
        return ls.getDays() >= rs.getDays();
    }

    bool operator<=(Date const& ls, Date const& rs)
    {
        return ls.getDays() <= rs.getDays();
    }

    bool operator<(Date const& ls, Date const& rs)
    {
        return ls.getDays() < rs.getDays();
    }

    bool operator>(Date const& ls, Date const& rs)
    {
        return ls.getDays() > rs.getDays();
    }

    int operator-(Date const& ls, Date const& rs)
    {
        int initial_days = ls.getDays();
        int final_day = rs.getDays();
        return initial_days - final_day;
    }

}
