#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace DynamicDecorator {
	struct Shape {
		virtual string str() const = 0;
	};

	struct Circle : Shape {
		float m_radius;

		Circle(float radius) : m_radius(radius){}

		string str() const override{
			ostringstream oss;
			oss << "This is a circle with radius: " << m_radius;
			return oss.str();
		}

		// this function won't be visible by decorators, since
		// decorators use Shape interface, so this method gets
		// sliced away :/
		void resize(float factor) {
			m_radius *= factor;
		}
	};

	struct ColoredShape : Shape {
		Shape& m_shape;
		string m_color;

		ColoredShape(Shape& shape, const string& color) : m_shape(shape), m_color(color){}

		virtual string str() const override
		{
			ostringstream oss;
			oss << m_shape.str() << " with color: " << m_color;
			return oss.str();
		}
	};

	struct TransparentShape : Shape {
		Shape& m_shape;
		float m_transparency;

		TransparentShape(Shape& shape, float transparency) : m_shape(shape), m_transparency(transparency){}

		virtual string str() const override
		{
			ostringstream oss;
			oss << m_shape.str() << " with transparency: " << m_transparency;
			return oss.str();
		}
	};
}

void DynamicDecoratorExample() {
	using namespace DynamicDecorator;

	Circle circle{ 3 };
	ColoredShape redCircle{ circle, "red" };
	TransparentShape transparentRedCircle{ redCircle, 50.0f };

	cout << circle.str() << endl << redCircle.str() << endl << transparentRedCircle.str() << endl;

	// only problem is that ColoredShape and TransparentShape both don't have acces to resize() method!
}