#include <iostream>

#include "Input.h"

template<typename T>
CodeErrors getValue(T& number) {
	std::cin.exceptions(std::istream::failbit | std::istream::badbit);
	std::cin.exceptions(std::istream::failbit | std::istream::eofbit);

	while (true) {
		std::cin >> number;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\nOoops! You input incorrect value. (symbol or other not numeric)" << std::endl;
		}
		else {
			return CodeErrors::SUCCESS;
		}
	}	
}

template CodeErrors getValue(int& number);
template CodeErrors getValue(double& number);
