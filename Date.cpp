#include<iostream>
#include<iomanip>
#include<cstring>
#include"Date.h"

using namespace std;

namespace aid {
	Date::Date() {
	
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_compare = 0;
		this->errCode(NO_ERROR);
	}
	
	Date::Date(int year, int month, int date) {
		

		bool validYear = (year >= min_year) && (year <= max_year);
		bool validMonth = (month >= 1) && (month <= 12);
		int daysInMonth = mdays(year, month);
		bool validDays = (daysInMonth != 13) && (daysInMonth >= date);

		if (validYear && validMonth && validDays) {
			m_year = year;
			m_month = month;
			m_day = date;
			m_compare = year * 372 + month * 31 + date;
			m_error = NO_ERROR;
		}
		else {
			*this = Date();
		};
	}
	int Date::errCode() const{
		return this->m_error;
	}

	int Date::errCode(int errorCode) {
	
		return this->m_error = errorCode;
	}
	
	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	bool Date::bad() const {
		if (m_error != 0) { return true; }
		else { return false;  }
	}

	std::istream& Date::read(std::istream& istr) {
		char slash;

		istr >> m_year >> slash >> m_month >> slash >> m_day;
		m_compare = m_year * 372 + m_month * 31 + m_day;

		if (istr.fail()) {
			*this = Date();
			this->errCode(CIN_FAILED);
			return istr;
		} else if (m_year > max_year || m_year < min_year) {
			*this = Date();
			this->errCode(YEAR_ERROR);
		}
		else if (m_month > 12 || m_month < 1) {
			*this = Date();
			this->errCode(MON_ERROR);
		}
		else if (m_day > mdays(m_year, m_month) || m_day < 1){
			*this = Date();
			this->errCode(DAY_ERROR);
		}
		else if(m_compare < min_date){
			*this = Date();
			this->errCode(PAST_ERROR);
		}
		else {
			return istr;
		}

		return istr;	
	}
	std::ostream& Date::write(std::ostream& ostr) const {
	
		char slash = '/';

		ostr << m_year << slash;
		ostr << setw(2) << setfill('0');
		ostr << m_month << slash;
		ostr << setw(2) << setfill('0');
		ostr << m_day;
		return ostr;
	}

	bool Date::isEmpty() const {
		if (this->m_year == 0) {	return true;	}
		else {	return false;	}
	}
	bool Date::operator==(const Date& rhs) const{

		bool result = *this != rhs;
		return !result;
	}
	bool Date::operator!=(const Date& rhs) const {
		if (!this->isEmpty() && !rhs.isEmpty()) {
			if (m_year != rhs.m_year || m_month != rhs.m_month || m_day != rhs.m_day) {

				return true;
			}
		}
		return false;
	}
	bool Date::operator<(const Date& rhs) const {
		if (!this->isEmpty() && !rhs.isEmpty()) {
			return this->m_compare < rhs.m_compare;
		}
		return false;
	}
	bool Date::operator>(const Date& rhs) const {
		bool result = *this < rhs;
		return !result;
	}

	bool Date::operator<=(const Date& rhs) const {
		if (!this->isEmpty() && !rhs.isEmpty()) {
			if (this->m_compare <= rhs.m_compare) {
				return true;
			}
		}
		return false;
	
	}
	bool Date::operator>=(const Date& rhs) const {
		if (!this->isEmpty() && !rhs.isEmpty()) {
			if (this->m_compare >= rhs.m_compare) {
				return true;
			}
		}
		return false;
	}

	std::istream& operator>>(std::istream& in, Date& date) {

		return date.read(in);
	}
	std::ostream& operator<<(std::ostream& os, const Date& date) {
		return date.write(os);
	}
};
