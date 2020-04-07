#ifndef AID_ERROR_H
#define AID_ERROR_H
#include<iostream>
using namespace std;

namespace aid {
	class Error{
		char* m_ptr;
	public:
		~Error();
		explicit Error(const char* errorMessage = nullptr);
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Error&);
}
#endif