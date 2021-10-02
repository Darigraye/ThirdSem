#pragma once

#include <iostream>

template<typename T>
void getValue(T& number, std::istream& in, std::ostream& out) { 
	in.exceptions(std::istream::eofbit | std::istream::badbit);

	while (true) {
		in >> number;

		if (in.fail()) {
			out << "\nOoops! You input incorrect value. (symbol or other not numeric)" << '\n';
			in.clear();
			in.ignore();										// DON'T IGNORE ALL SYMBOLS ESPECIALLY FOR MULTI-THREADING!!!!!!!
		}
		else {
			break;
		}
	}
}