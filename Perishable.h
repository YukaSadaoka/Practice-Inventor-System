#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H
#include <iostream>
#include <fstream>
#include <string>
#include "Good.h"
#include "Date.h"
#include "iGood.h"

namespace aid {

	class Perishable : public Good {
		Date date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& in);
		const Date& expiry() const;
	};

}
#endif
