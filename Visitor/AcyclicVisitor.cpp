#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/// <summary>
/// This implementation of the visitor pattern uses Run-time type information (RTTI)
/// https://en.wikipedia.org/wiki/Run-time_type_information
/// 
/// So it's slow, but doesn't force any hierarchies on our code
/// </summary>
namespace AcyclicVisitor {
	
	template <typename Visitable>
	struct Visitor {
		virtual void Visit(Visitable& obj) = 0;
	};

	struct VisitorBase {
		// need vtables to be created, so we include a virtual destructor here
		virtual ~VisitorBase() = default;
	};

	struct Expression {

		// obj should ACTUALLY be of type Visitor<Expression>
		virtual void Accept(VisitorBase& obj) {
			// we use using instead of typedef because it works better with templates?
			// I don't really know: https://stackoverflow.com/questions/10747810/what-is-the-difference-between-typedef-and-using-in-c11
			using EV = Visitor<Expression>;
			if (auto ev = dynamic_cast<EV*>(&obj)) {
				ev->Visit(*this);
			}
		}

		virtual ~Expression() = default;
	};

	struct DoubleExpression : Expression {
		double m_value;
		DoubleExpression(double value) : m_value(value) {}

		// obj should ACTUALLY be of type Visitor<DoubleExpression>
		virtual void Accept(VisitorBase& obj) {
			using DEV = Visitor<DoubleExpression>;
			if (auto ev = dynamic_cast<DEV*>(&obj)) {
				ev->Visit(*this);
			}
		}
	};

	struct AdditionExpression : Expression {
		Expression *m_left, *m_right;

		AdditionExpression(Expression* left, Expression* right) : m_left(left), m_right(right){}
		
		// obj should ACTUALLY be of type Visitor<AdditionExpression>
		virtual void Accept(VisitorBase& obj) {
			using DEV = Visitor<AdditionExpression>;
			if (auto ev = dynamic_cast<DEV*>(&obj)) {
				ev->Visit(*this);
			}
		}

		~AdditionExpression() {
			delete m_left;
			delete m_right;
		}
	};

	/// <summary>
	/// ExpressionPrinter MUST inherit from all the types specified.
	/// If it doesn't, then the other Accept() function will be skipped. 
	/// 
	/// Example, if ExpressionPrinter does NOT inherit from Visitor<DoubleExpression>,
	/// then DoubleExpression::Accept() won't do anything because the dynamic cast will fail
	/// </summary>
	struct ExpressionPrinter : VisitorBase,
		Visitor<DoubleExpression>,
		Visitor<AdditionExpression> {
		
		void Visit(DoubleExpression& obj) override {
			m_oss << obj.m_value;
		}

		void Visit(AdditionExpression& obj) override {
			m_oss << "(";
			obj.m_left->Accept(*this);
			m_oss << "+";
			obj.m_right->Accept(*this);
			m_oss << ")";
		}

		string str() const { return m_oss.str(); }
	private:
		ostringstream m_oss;
	};
}

void AcyclicVisitorExample() {
	using namespace AcyclicVisitor;

	auto e = new AdditionExpression{
		new DoubleExpression{1},
		new AdditionExpression{
			new DoubleExpression{2},
			new DoubleExpression{3}
		}
	};

	ExpressionPrinter ep;
	ep.Visit(*e);
	cout << ep.str() << endl;
}