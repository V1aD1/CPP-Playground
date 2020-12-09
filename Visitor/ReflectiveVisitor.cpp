#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

namespace ReflectiveVisitorNamespace {
	struct Expression {
		virtual ~Expression() = default;
	};

	struct DoubleExpression : Expression {
		double m_value;

		DoubleExpression(double value) : m_value(value) {}
	};

	struct AdditionExpression : Expression {

		//  1 + 2 + 3
		//    +
		//   / \
		//  1   +
		//     / \
		//    2   3

		Expression* m_left, * m_right;

		AdditionExpression(Expression* left, Expression* right) : m_left(left), m_right(right) {}

		~AdditionExpression() {
			delete m_left;
			delete m_right;
		}
	};

	struct ExpressionPrinter {
		ostringstream m_oss;

		/// <summary>
		/// This works, AND doesn't violate open closed principle!!
		/// 
		/// But there are drawbacks. 
		/// For one, dynamic_cast is an expensive operation. 
		/// But a bigger problem is that this ALSO doesn't scale well, the print()
		/// function will need to be modified every time a new Expression type is created!
		/// </summary>
		void print(Expression* e) {
			if (auto de = dynamic_cast<DoubleExpression*>(e)) {
				m_oss << de->m_value;
			}
			else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
				m_oss << "(";
				print(ae->m_left);
				m_oss << "+";
				print(ae->m_right);
				m_oss << ")";
			}
		}

		string str() const { return m_oss.str(); }
	};
}

void ReflectiveVisitorExample() {
	using namespace ReflectiveVisitorNamespace;

	AdditionExpression expr{
		new DoubleExpression{1},
		new AdditionExpression{
			new DoubleExpression(2),
			new DoubleExpression(3)
		}
	};

	// want to print (1+(2+3))
	ExpressionPrinter printer{};
	printer.print(&expr);
	cout << printer.str();
}