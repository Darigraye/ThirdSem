#pragma once
#include <iostream>

#include "Point.h"
#include "Errors.h"


class Tractriss {
private:
	double m_distance; // from the point of 
					   // touch to intersection with Ox	

	bool beloningOfRange(const double phi_1, const double phi_2) const; // for some functions
	bool beloningOfRange(const double phi) const;
public:
	explicit Tractriss(double distance = 0);

	inline Tractriss(const Tractriss& tractriss) : Tractriss{ tractriss.m_distance }
	{

	}

	~Tractriss() = default;

	double getRadius(const double phi) const;
	CodeErrors getCoordinates(const double phi, Point& outPoint) const;
	inline double getDistance() const { return m_distance; }
	inline void setDistance(const double newDistance) { m_distance = (newDistance > 0) ? newDistance : m_distance; }
	double getArea() const;
	double getVolume() const;
	double getSurface() const;
	double getDougieLength(const double phi_1, const double phi_2) const; // in radians


	Tractriss& operator=(Tractriss tractriss);
	friend std::ostream& operator<<(std::ostream& out, const Tractriss& tractriss);
};