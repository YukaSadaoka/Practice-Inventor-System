#include <iostream>
#include <fstream>
#include <string>
#include "Perishable.h"
#include "iGood.h"
#include "Good.h"
#include "Date.h"
using namespace std;

namespace aid {

	Perishable::Perishable(): Good::Good('P') {	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, newLine);
		Date temp = expiry();
		if (!file.fail()) {			
			file << ',' << temp;
			if (newLine == true) {
				file << endl;
			}
		}
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		
		if (!file.fail()) {
			date.read(file);
		}
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		this->Good::write(os, linear);
		 
		if (this->isClear() && !this->Good::isEmpty()) {
			if (linear){
			
				this->date.write(os);
			}
			else {
				os << "\n" << " Expiry date: ";
				this->date.write(os);
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& in) {
		Good::read(in);
	
		Date temp;
		if (!in.fail()) {

			cout << " Expiry date (YYYY/MM/DD): ";
			temp.read(in);
			int errorState = temp.errCode();

			if (errorState != 0) {

				in.setstate(std::ios::failbit);

				if (errorState == 1) {

					message("Invalid Date Entry");
				}
				else if (errorState == 2) {

					this->Good::message("Invalid Day in Date Entry");
				}
				else if (errorState == 3) {

					this->Good::message("Invalid Month in Date Entry");
				}
				else if (errorState == 4) {

					this->Good::message("Invalid Year in Date Entry");
				}
				else {

					this->Good::message("Invalid Expiry in Date Entry");
				}
				
			}
			else {
				this->date = temp;
			}
		}
		return in;
	}
	const Date& Perishable::expiry() const {
		return date;
	}
	iGood* CreateProduct(char tag) {
		iGood* good_ptr = nullptr;

		if (tag == 'N' || tag == 'n') {
			good_ptr = new Good('N');
		}
		else if(tag == 'P' || tag == 'p' ){
			good_ptr = new Perishable();
		}else {
			return nullptr;
		}

		return good_ptr;
	}
}

