#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Point {
	float m_x, m_y;
	Point(float x, float y) : m_x(x), m_y(y) {}
	friend ostream& operator<<(ostream& os, const Point& point) {
		os << "x: " << point.m_x << " y: " << point.m_y;
		return os;
	}
};

struct PointFactory {
	// Factory method
	static Point NewCartesian(float x, float y) {
		return { x, y };
	}

	// Factory method
	static Point NewPolar(float r, float theta) {
		return { r * cos(theta), r * sin(theta) };
	}
};

void FactoryExample() {
	// M_PI_4 = pi/4
	auto p1 = PointFactory::NewPolar(5, M_PI_4);
	auto p2 = PointFactory::NewCartesian(1, 2);

	cout << p1 << endl;
	cout << p2 << endl;
}