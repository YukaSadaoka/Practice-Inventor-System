#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Good.h"
#include "Error.h"

using namespace std;

namespace aid {
	void Good::name(const char* name) {

		if (m_name != nullptr) {
			delete[] m_name;
		}
		if (name != nullptr && name[0] != '\0') {
			int len = strlen(name);
			m_name = new char[len + 1];
			strncpy(m_name, name, len);
			m_name[len] = '\0';
		}
		if (name == nullptr) {
			m_name = nullptr;
		}
	}
	const char* Good::name() const {
		
		if (m_name != nullptr) {
			return m_name;
		}
		else {
			return nullptr;
		}
	}
	const char* Good::sku() const {
		return m_SKU;
	}
	const char* Good::unit() const {
		return m_unit;
	}
	bool Good::taxed() const {
		return m_taxable;
	}
	double Good::itemPrice() const {
		return m_price;
	}
	double Good::itemCost() const {
		if (m_taxable) {
			return m_price * (1 +  tax_rate);
		}
		else {
			return m_price;
		}
	}
	void Good::message(const char* errorMessage) {

		error.message(errorMessage);
	}
	bool Good::isClear() const {
		return error.isClear();
	}

	// public functions
	Good::Good(char type) {
		m_type = type;
		m_SKU[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		m_onHand = 0;
		m_itemNeeded = 0;
		m_price = 0.0;
		m_taxable = false; 
	}
	Good::Good(const char* SKU, const char* name, const char* unit, int numItem, bool taxable, double price, int itemNeeded) {

		m_name = nullptr;
		this->name(name);
		m_type = '0';

		if (SKU != nullptr && SKU[0] != '\0') {
			strncpy(m_SKU, SKU, max_sku_length);
				m_SKU[max_sku_length] = '\0';
		}
		else {
			m_SKU[0] = '\0';
		}

		if (unit != nullptr && unit[0] != '\0') {
			strncpy(m_unit, unit, max_unit_length);
			m_unit[max_unit_length] = '\0';
		}
		else {
			m_unit[0] = '\0';
		}

		if (numItem >= 0) {
			m_onHand = numItem;
		}
		else {
			m_onHand = 0;
		}

		m_taxable = taxable;

		if (price >= 0) {
			m_price = price;
		}
		else {
			m_price = 0.0;
		}

		if (itemNeeded >= 0) {
			m_itemNeeded = itemNeeded;
		}
		else {
			m_itemNeeded = 0;
		}
	}
	Good::Good(const Good& other) {
		m_name = nullptr;
		*this = other;
	}
	
	Good& Good::operator=(const Good& other) {

		if (this != &other) {

			name(other.m_name);
			m_type = other.m_type;

			strncpy(this->m_SKU, other.m_SKU, max_sku_length); 
			this->m_SKU[max_sku_length] = '\0';

			strncpy(this->m_unit, other.m_unit, max_unit_length);
			m_unit[max_unit_length] = '\0';

			this->m_onHand = other.m_onHand;
			m_taxable = other.m_taxable;
			m_price = (other).m_price;
			this->m_itemNeeded = other.m_itemNeeded;
			m_type = other.m_type;
		}
		return *this;
	}
	Good::~Good() {
		delete[] m_name;
		m_name = nullptr;
	}
	std::fstream& Good::store(std::fstream& file, bool newLine) const {
	
		file << m_type << ',' << m_SKU << ','
			<< m_name << ',' << m_unit << ',' <<
			m_taxable << ',' << m_price << ','
			<< m_onHand << ',' << m_itemNeeded;
			
			if (newLine == true && m_type == 'N') {
				file << endl;
			}
		return file;
	}
	std::fstream& Good::load(std::fstream& file) {
		
		Good temp;
		temp.m_name = new char[max_name_length + 1];
	

		 if (file.is_open()) {
			 file.getline(temp.m_SKU, max_sku_length, ',');
			 file.getline(temp.m_name, max_name_length, ',');
			 file.getline(temp.m_unit,  max_unit_length, ',');
			 
			 file >> temp.m_taxable;
			 file.ignore();
			 file >> temp.m_price;
			 file.ignore();
			 file >> temp.m_onHand;
			 file.ignore();
			 file >> temp.m_itemNeeded;
			 file.ignore();
		}

		*this = temp;
		
		delete[] temp.m_name;
		temp.m_name = nullptr;

		return file;
	}
	std::ostream& Good::write(std::ostream& os, bool linear)const {
		
		double taxedPrice = 0.0;
		
		if (!this->error.isClear())
		{
			os << this->error.message();
			return os;

		}else if (this->isEmpty()) {
			return os;		
		}
		else {
			if (linear) {

				os << setfill(' ') << setw(max_sku_length) << left << m_SKU << '|' <<
					setfill(' ') << setw(20) << left << m_name << '|' << setfill(' ') << setw(7)
					<< right << fixed << setprecision(2);
					
				if (m_taxable) {
					taxedPrice = m_price * (1 + tax_rate);
				}
				else {
					taxedPrice = m_price;
				}

				os << taxedPrice << '|' << setfill(' ') << setw(4) << right << m_onHand << '|' <<
					setfill(' ') << setw(10) << left << m_unit << '|' << setfill('0') <<
					setw(4) << right << m_itemNeeded << '|';
			}
			else {
				os << " Sku: " << m_SKU << endl;
				os << " Name (no spaces): " << m_name << endl;
				os << " Price: " << m_price << endl;

				if (m_taxable) {
					os << " Price after tax: " << total_cost() << endl;
				}
				else {
					os << " Price after tax:  N/A" << endl;
				}

				os << " Quantity on Hand: " << m_onHand << " " << m_unit << endl
					<< " Quantity needed: " << m_itemNeeded;
			}
		}
		return os;
	}
	std::istream& Good::read(std::istream& is) {
		
		char* name = new char[max_name_length + 1];
		char yesNo;
		char currentType = this->m_type;
		Good temp;

		bool noError = true;

		cout << " Sku: ";
		is >> temp.m_SKU;

		cout << " Name (no spaces): ";
		is >> name;
		temp.name(name);

		cout << " Unit: ";
		is >> temp.m_unit;

		cout << " Taxed? (y/n): ";
		is >> yesNo;

		if (yesNo == 'y' || yesNo == 'Y') {
			temp.m_taxable = true;
		}
		else if (yesNo == 'N' || yesNo == 'n') {
			temp.m_taxable = false;
		}
		else {
			is.setstate(std::ios::failbit);
			this->error.message("Only (Y)es or (N)o are acceptable");
			return is;
		}

		if (!is.fail()) {
			cout << " Price: ";
			is >> temp.m_price;

			if (is.fail()) {
				temp.error.message("Invalid Price Entry");
				noError = false;
			}
		}
		if (!is.fail()) {
			cout << " Quantity on hand: ";
			is >> temp.m_onHand;

			if (is.fail()) {
				temp.error.message("Invalid Quantity Entry");
				noError = false;
			}
		}
		if (!is.fail()) {
			cout << " Quantity needed: ";
			is >> temp.m_itemNeeded;

			if (is.fail()) {
				temp.error.message("Invalid Quantity Needed Entry");
				noError = false;
			}
		}

		if (!is.fail()) {			
			*this = temp;
			this->m_type = currentType;
		}

		if (noError) {
			this->error.clear();
		}
		else {
			this->message(temp.error.message());
		}
		delete[] name;
		name = nullptr;
		
		return is;
	
	}
	bool Good::operator==(const char* sku) const {
		if (this->m_SKU != sku) {
			return true;
		}
		else {
			return false;
		}
	}
	double Good::total_cost() const {
		
		double tax = 0.0;
		if (m_taxable) {
			tax = m_price * tax_rate;
		}
		double taxedPrice = m_price + tax;
		return  taxedPrice * m_onHand;
		

		return m_price * m_onHand;
	}
	void Good::quantity(int units) {
		if (units > 0) {
			m_onHand = units;
		}
	}
	bool Good::isEmpty() const {
		if( m_name == nullptr){
			return true;
		}
		else {
			return false;
		}
	}
	int Good::qtyNeeded() const {
		return m_itemNeeded;
	}
	int Good::quantity() const {
		return m_onHand;
	}
	
	bool Good::operator>(const char* SKU)const {
		if (strcmp(m_SKU, m_SKU) < 0)
		{
			return true;
		}
		else {
			return false;
		}
	}
	bool Good::operator>(const iGood& other) const {
		
		if (!this->isEmpty() && Good::isEmpty()) {
			if (strcmp(this->m_name, Good::m_name) < 0)
			{
				return true;
			}
		}

		return false;
	}
	int Good::operator+=(int units) {
		if (units > 0) {
			this->m_onHand += units;
			return this->m_onHand;
		}
		else {
			return this->m_onHand;
		}
	}

	//healper
	std::ostream& operator<<(std::ostream& os, const iGood& other){
		return other.write(os, true);
	}
	std::istream& operator>>(std::istream& in, iGood& other) {
		return other.read(in);
	}
	double operator+=(double& total, const iGood& other) {
		return total + other.total_cost();
	}
}
