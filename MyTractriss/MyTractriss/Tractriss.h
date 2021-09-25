#pragma once
#include <iostream>

#include "Point.h"
#include "Errors.h"


class Tractriss {
private:
	double m_distance; // from the point of 
					   // touch to intersection with Ox	

	bool beloningOfRange(const double phi_1, const double phi_2) const noexcept; // for some functions
	bool beloningOfRange(const double phi) const noexcept;
public:
	explicit Tractriss(double distance = 0);

	inline Tractriss(const Tractriss& tractriss) : Tractriss{ tractriss.m_distance }
	{

	}

	~Tractriss() = default;

	double getRadius(const double phi) const;
	Point getCoordinates(const double phi) const;
	inline double getDistance() const noexcept { return m_distance; }
	void setDistance(const double newDistance);
	double getArea() const noexcept;
	double getVolume() const noexcept;
	double getSurface() const noexcept;
	double getDougieLength(const double phi_1, const double phi_2) const; // in radians


	Tractriss& operator=(Tractriss tractriss);
	friend std::ostream& operator<<(std::ostream& out, const Tractriss& tractriss);
};