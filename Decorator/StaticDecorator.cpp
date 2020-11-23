#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace StaticDecorator {
	struct Shape {
		virtual string str() const = 0;
	};

	struct Circle : Shape {
		float m_radius;

		Circle(float radius) : m_radius(radius) {}

		string str() const override {
			ostringstream oss;
			oss << "This is a circle with radius: " << m_radius;
			return oss.str();
		}

		// this function WILL be visible in a static decorator
		void resize(float factor) {
			m_radius *= factor;
		}
	};

	/// <summary>
	/// Uses constructor forwarding to expose all members of type T
	/// </summary>
	template <typename T> struct ColoredShape : T {
		string m_color;

		ColoredShape() {}

		// perfect forwarding...
		template<typename...Args>
		ColoredShape(const string& color, Args ...args) : T(std::forward<Args>(args)...), m_color(color) {}
	
		string str() const override {
			ostringstream oss;
			oss << T::str() << " has the color: " << m_color;
			return oss.str();
		}
	};

	template <typename T> struct TransparentShape : T {
		float m_transparency;

		// perfect forwarding...
		template<typename...Args>
		TransparentShape(float transparency, Args ...args) : T(std::forward<Args>(args)...), m_transparency(transparency) {}

		string str() const override
		{
			ostringstream oss;
			oss << T::str() << " with transparency: " << m_transparency;
			return oss.str();
		}
	};
}

void StaticDecoratorExample() {
	using namespace StaticDecorator;
	
	// we now have access to the resize() function!
	ColoredShape<Circle> greenCircle{"green", 5};
	greenCircle.resize(2.0f);
	cout << greenCircle.str() << endl;

	TransparentShape<ColoredShape<Circle>> transparentColoredCircle{ 50.0f, "red", 5 };
	cout << transparentColoredCircle.str() << endl;
	cout << "Changing circle properties..." << endl;

	// better yet, we have access to all members from TransparentShape, ColoredShape, and Circle!
	transparentColoredCircle.m_color = "blue";
	transparentColoredCircle.resize(2.0f);
	transparentColoredCircle.m_transparency = 10.0f;
	cout << transparentColoredCircle.str() << endl;
}