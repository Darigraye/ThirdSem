#include <iostream>

#include "Interface.h"
#include "Input.h"

using std::cout;
using std::endl;

void Interface::menu() {
	int mode;

	try {
		do {
			for (auto& current : m_messages) {
				cout << current << endl;
			}

			getValue(mode);

			if (mode < minSizeMenu || mode > maxSizeMenu) {
				cout << "Ooops! You input incorrect value" << endl;

				continue;
			}

			if (m_mode == ModeInterface::NULL_VALUE && mode > 2 && mode != 9) {
				cout << "Curve undefined" << endl;

				continue;
			}

			switch (mode) {
			case 0:
				break;
			case 1:
				double distance;
				cout << "Input distance: " << endl;

				getValue(distance);

				m_tractriss.setDistance(distance);
				m_mode = (distance <= 0) ? ModeInterface::NULL_VALUE : ModeInterface::INIT;

				break;
			case 2:
				cout << "Distance = " << m_tractriss.getDistance() << endl;
				break;
			case 3:
				cout << "Area = " << m_tractriss.getArea() << endl;
				break;
			case 4:
				cout << "Volume = " << m_tractriss.getVolume() << endl;
				break;
			case 5:
				cout << "Area of surface = " << m_tractriss.getSurface() << endl;
				break;
			case 6:
				double phi_1,
					phi_2;
				cout << "Input degrees of the corners (in radians): ";

				getValue(phi_1);
				getValue(phi_2);

				if (m_tractriss.getDougieLength(phi_1, phi_2) == -1) {
					cout << "Corner doesn't fall into range or " <<
						" first corner have more value then second" << endl;
				}
				else {
					std::cout << "Lenght of dougie = " <<
						m_tractriss.getDougieLength(phi_1, phi_2) << endl;
				}

				break;
			case 7:
				double phi;
				cout << "Input degree of the corner (in radians): ";

				getValue(phi);

				if (m_tractriss.getRadius(phi) == -1) {
					cout << "Corner doesn't fall into range" << endl;
				}
				else {
					cout << "Radius = " << m_tractriss.getRadius(phi) << endl;
				}

				break;
			case 8:
				double alpha;
				Point point; // point whose coordinates we want to get

				cout << "Input degree of the corner (in radians): ";

				getValue(alpha);

				if (m_tractriss.getCoordinates(alpha, point) == CodeErrors::USER_FAIL) {
					cout << "Corner doesn't fall into range" << endl;
				}
				else {
					cout << "x = " << point.x << " or x = " << -point.x <<
						"; y = " << point.y << endl;
				}
				break;
			case 9:
				cout << m_tractriss << endl;
				break;
			}
		} while (mode != 0);
	}
	catch (const std::istream::failure& exc) {
		std::cout << exc.what() << std::endl;
		return;
	}
}
