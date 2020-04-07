#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include"Error.h"

using namespace std;

namespace aid {
	Error::~Error() {
		delete[] m_ptr;
		m_ptr = nullptr;
	}
	Error::Error(const char* errorMessage) {
		m_ptr = nullptr;
		if (errorMessage != nullptr && errorMessage[0] != '\0') {
			delete[] m_ptr;
			int len = strlen(errorMessage);
			m_ptr = new char[len + 1];
			
			strncpy(m_ptr, errorMessage, len);
			m_ptr[len] = '\0';
		}
		else {
			m_ptr = nullptr;
		}
	}
	void Error::clear() {

		delete[] m_ptr;
		m_ptr = nullptr;
	}
	bool Error::isClear() const {
		if (m_ptr == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void Error::message(const char* str) {
		
		if (str != nullptr && str[0] != '\0') {
			if (!this->isClear()) {
				delete[]  m_ptr;
			} 
			int len = strlen(str);
			m_ptr = new char[len + 1];
			strncpy(this->m_ptr, str, len);
			m_ptr[len] = '\0';
		}
		else {
			m_ptr = nullptr;
		}
	}
	const char* Error::message() const {
		if (!isClear()) {
			return m_ptr;
		}
		else {
			return nullptr;
		}
	}
	std::ostream& operator<<(std::ostream & ostr, const Error& error) {
		if (!error.isClear()) {
			ostr << error.message();
		}
		return ostr;
	}

}