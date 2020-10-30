#include <iostream>
using namespace std;

/// <summary>
/// Functions that use pointers or references to base classes 
/// must be able to use objects of derived classes without knowing it.
/// </summary>

struct Rectangle {
protected:
	int m_width, m_height;

public:
	Rectangle(int width, int height) : m_width(width), m_height(height) {}

	int getHeight() const{
		return m_height;
	}
	int getWidth() const {
		return m_width;
	}
	virtual void setHeight(int value) {
		m_height = value;
	}
	virtual void setWidth(int value) {
		m_height = value;
	}
	int getArea() const{
		return m_width * m_height;
	}
};

/// <summary>
/// Squares have the same length and width, therefore setting either width or height
/// must ALSO set the OTHER side length
/// </summary>
struct Square : Rectangle {
	Square(int size): Rectangle(size, size){}

	void setHeight(int value) override {
		m_height = m_width = value;
	}
	void setWidth(int value) override {
		m_height = m_width = value;
	}
};

bool ValidateRectangleAreaTest(Rectangle& rect) {
	int width = rect.getWidth();
	rect.setHeight(10);

	// area should be width*10, if it isn't return false
	return rect.getArea() == width * 10;
}

void LiskovSubstitutionExample() {
	Rectangle rect{3, 4};
	cout << "Is rect valid? " << ValidateRectangleAreaTest(rect) << endl;

	// Uh oh, square fails because when width changes, so does height.
	// This indicates that our abstraction/ inheritance hierarchy is poorly designed
	Square square{ 5 };
	cout << "Is square valid? " << ValidateRectangleAreaTest(square) << endl;

}