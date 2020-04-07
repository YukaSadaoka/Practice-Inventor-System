#ifndef AID_DATE_H
#define AID_DATE_H
#include <iostream>

#define NO_ERROR 0 
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3 
#define YEAR_ERROR 4 
#define PAST_ERROR 5 

namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {

		int m_year;
		int m_month;
		int m_day;
		int m_compare;
		int m_error;

		bool isEmpty() const;
		int mdays(int year, int month) const;
		int errCode(int errorCode);
	public:

		Date();
		Date(int, int, int);

		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

		
		bool operator==(const Date& rhs) const; 
		bool operator!=(const Date& rhs) const; 
		bool operator<(const Date& rhs) const; 
		bool operator>(const Date& rhs) const; 
		bool operator<=(const Date& rhs) const; 
		bool operator>=(const Date& rhs) const;
	};
	std::istream& operator>>(std::istream& in, Date&);
	std::ostream& operator<<(std::ostream& os,const Date& date);
}

#endif