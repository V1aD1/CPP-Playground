#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

namespace IntrusiveVisitorNamespace {
	struct Expression {
		virtual ~Expression() = default;

		// this print() function, which was added after the Expression class was created,
		// is the intrusive visitor
		virtual void print(ostringstream& oss) = 0;
	};

	struct DoubleExpression : Expression {
		double m_value;

		DoubleExpression(double value) : m_value(value){}

		void print(ostringstream& oss) override {
			oss << m_value;
		}
	};

	struct AdditionExpression : Expression {
		
		//  1 + 2 + 3
		//    +
		//   / \
		//  1   +
		//     / \
		//    2   3
		
		Expression *m_left, *m_right;

		AdditionExpression(Expression* left, Expression* right) : m_left(left), m_right(right) {}
	
		void print(ostringstream& oss) override {
			oss << "(";
			m_left->print(oss);
			oss << "+";
			m_right->print(oss);
			oss << ")";
		}

		~AdditionExpression() {
			delete m_left;
			delete m_right;
		}
	};
}

void IntrusiveVisitorExample(){
	using namespace IntrusiveVisitorNamespace;

	AdditionExpression expr{
		new DoubleExpression{1},
		new AdditionExpression{
			new DoubleExpression(2),
			new DoubleExpression(3)
		}
	};

	// want to print (1+(2+3))
	// the intrusive visitor would just add a print() to each expression,
	// thereby violating the open closed principle
	// In this case it isn't difficult, but in more complex systems it would be very cumbersome
	ostringstream oss;
	expr.print(oss);
	cout << oss.str();
}