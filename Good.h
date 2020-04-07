#ifndef AID_GOOD_H
#define AID_GOOD_H
#include <iostream>
#include <fstream>
#include <string>
#include "Error.h"
#include "iGood.h"

namespace aid {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood {
		char m_type;
		char m_SKU[max_sku_length + 1];
		char m_unit[max_unit_length + 1];
		char* m_name;
		int m_onHand;
		int m_itemNeeded;
		double m_price;
		bool m_taxable;
		Error error;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Good(char type = 'N');
		Good(const char* SKU, const char* name, const char* unit, int numItem = 0, bool taxable = true, double price = 0.0, int itemNeeded = 0);
		Good(const Good&);
		Good& operator=(const Good&);
		~Good();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int units);
	};
}

#endif