#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace FactoryMethod {
	enum class PointType {
		cartesian,
		polar
	};

	struct BadPoint {
		float m_x, m_y;

		// Cartesian coords
		//BadPoint(float x, float y) : m_x(x), m_y(y) {}

		// Polar coords
		// Uh oh we can't have multiple constructors with the same signature in C++!
		//Point(float rho, float theta) {}

		// Ok, this technically works, BUT it isn't clear that a corresponds to x/ rho value
		// and that b corresponds to y/ theta value. We'd have to leave comments in order to
		// specify that. So this is ALSO bad.
		BadPoint(float a, float b, PointType type = PointType::cartesian) {
			if (type == PointType::cartesian) {
				m_x = a;
				m_y = b;
			}
			else {
				m_x = a * cos(b);
				m_y = a * sin(b);
			}
		}
	};

	class Point {
		float m_x, m_y;
		Point(float x, float y) : m_x(x), m_y(y) {}
	public:
		// Factory method
		static Point NewCartesian(float x, float y) {
			return { x, y };
		}

		// Factory method
		static Point NewPolar(float r, float theta) {
			return { r * cos(theta), r * sin(theta) };
		}

		friend ostream& operator<<(ostream& os, const Point& point) {
			os << "x: " << point.m_x << " y: " << point.m_y;
			return os;
		}
	};
}

void FactoryMethodExample() {
	using namespace FactoryMethod;

	// M_PI_4 = pi/4
	auto p1 = Point::NewPolar(5, M_PI_4);
	auto p2 = Point::NewCartesian(1, 2);

	cout << p1 << endl;
	cout << p2 << endl;
}