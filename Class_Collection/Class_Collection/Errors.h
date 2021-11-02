#pragma once

#include <string>

class Exception { // primitive realization
private:
	std::string m_msgExc;

public:
	inline explicit Exception(const std::string msg) noexcept { m_msgExc = msg; }

	inline std::string what() const noexcept { return m_msgExc; }
};