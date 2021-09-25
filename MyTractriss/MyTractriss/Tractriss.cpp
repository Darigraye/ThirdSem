#include "pch.h"

#include <cmath>
#include <iostream>
#include <utility>

#include "Tractriss.h"
#include "Errors.h"
#include "Point.h"

using std::pow;
using std::log;
using std::abs;
using std::tan;

constexpr double pi = 3.141592653589793;

bool Tractriss::beloningOfRange(const double phi_1, const double phi_2) const noexcept {
	if (phi_1 >= pi || phi_2 >= pi || phi_1 <= 0 || phi_2 <= 0 || phi_2 < phi_1) {
		return false;
	}

	return true;
}

bool Tractriss::beloningOfRange(const double phi) const noexcept {
	if (phi <= 0 || phi >= pi) {
		return false;
	}

	return true;
}

Tractriss::Tractriss(double distance) : m_distance{ distance }
{
	if (distance < 0) {
		throw Exception("Incorrect distance! Value < 0");
	}
}

void Tractriss::setDistance(double value) {
	if (value < 0) {
		throw Exception("Incorrect distance! Value < 0");
	}

	m_distance = value;
}

double Tractriss::getArea() const noexcept {
	return (pow(m_distance, 2) * pi) / 2;
}

double Tractriss::getVolume() const noexcept {
	return 2 * (pi * pow(m_distance, 3) / 3);
}

double Tractriss::getSurface() const noexcept {
	return 4 * pi * pow(m_distance, 2);
}

double Tractriss::getDougieLength(const double phi_1, const double phi_2) const {
	if (beloningOfRange(phi_1, phi_2) == false) { 
		throw Exception("Angles out of range");
	}

	return m_distance * abs(log(abs(sin(phi_1) / sin(phi_2))));
}


double Tractriss::getRadius(const double phi) const {
	if (beloningOfRange(phi) == false) {
		throw Exception("Angle out of range");
	}

	return m_distance / abs(tan(phi));
}

Point Tractriss::getCoordinates(const double phi) const {
	if (beloningOfRange(phi) == false) {
		throw Exception("Angle out of range");
	}

	Point point;

	point.x = m_distance * (log(tan(phi / 2)) + cos(phi));
	point.y = m_distance * abs(sin(phi)); // we use abs because y must be only positive;

	return point;
}

std::ostream& operator<< (std::ostream& out, const Tractriss& tractriss) {
	if (tractriss.m_distance == 0) {
		out << "There is no such curve" << std::endl;

		return out;
	}

	out << "The equation of tractriss: \n";
	out << "x = (+/-) " << tractriss.m_distance << " * ln((" << tractriss.m_distance;
	out << " + sqrt( " << tractriss.m_distance << "^2 - y^2 )) / y) - sqrt( ";
	out << tractriss.m_distance << "^2 - y^2 )" << std::endl;

	return out;
}

Tractriss& Tractriss::operator=(Tractriss tractriss) {
	std::swap(this->m_distance, tractriss.m_distance); // keep it simple

	return *this;
}