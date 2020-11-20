#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/// <summary>
/// Even though we have a factory, we aren't telling the developer that they HAVE to use the factory.
/// So we're going to fix that by using an inner factory.
/// </summary>
namespace InnerFactory {
	class Point {
		float m_x, m_y;

		// the constructor is private
		Point(float x, float y) : m_x(x), m_y(y) {}

		// this is an inner factory, but it's private. We have to expose it with a public member. 
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

	public:
		// exposing the factory here
		static PointFactory factory;
		friend ostream& operator<<(ostream& os, const Point& point) {
			os << "x: " << point.m_x << " y: " << point.m_y;
			return os;
		}
	};
}

void InnerFactoryExample() {
	using namespace InnerFactory;

	// M_PI_4 = pi/4
	auto p1 = Point::factory.NewPolar(5, M_PI_4);
	auto p2 = Point::factory.NewCartesian(1, 2);

	cout << p1 << endl;
	cout << p2 << endl;
}