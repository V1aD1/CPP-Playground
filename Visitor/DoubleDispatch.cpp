#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/// <summary>
/// This is the CLASSIC visitor implementation
/// </summary>

namespace DoubleDispatchNamespace {

	struct DoubleExpression;
	struct AdditionExpression;
	struct SubtractionExpression;

	struct ExpressionVisitor {
		virtual void visit(DoubleExpression* de) = 0;
		virtual void visit(AdditionExpression* ae) = 0;
		virtual void visit(SubtractionExpression* se) = 0;
	};

	struct ExpressionPrinter : ExpressionVisitor {
		ostringstream m_oss;

		string str() const { return m_oss.str(); }

		virtual void visit(DoubleExpression* de) override;
		virtual void visit(AdditionExpression* ae) override;
		virtual void visit(SubtractionExpression* se) override;

	};

	struct ExpressionEvaluator : ExpressionVisitor {
		double m_result;

		virtual void visit(DoubleExpression* de) override;
		virtual void visit(AdditionExpression* ae) override;
		virtual void visit(SubtractionExpression* se) override;

	};

	struct Expression {

		// Accept() is the name of the dispatch method, by convention
		virtual void Accept(ExpressionVisitor* visitor) = 0;
		virtual ~Expression() = default;
	};

	struct DoubleExpression : Expression {
		double m_value;

		DoubleExpression(double value) : m_value(value) {}

		virtual void Accept(ExpressionVisitor* visitor) override
		{
			// as long as there is a visit method specified for this class, it will be called
			visitor->visit(this);
		}
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

		// Inherited via Expression
		virtual void Accept(ExpressionVisitor* visitor) override
		{
			// as long as there is a visit method specified for this class, it will be called
			visitor->visit(this);
		}
	};

	struct SubtractionExpression : Expression {
		Expression* m_left, * m_right;

		SubtractionExpression(Expression* left, Expression* right) : m_left(left), m_right(right) {}

		~SubtractionExpression() {
			delete m_left;
			delete m_right;
		}

		// Inherited via Expression
		virtual void Accept(ExpressionVisitor* visitor) override
		{
			// as long as there is a visit method specified for this class, it will be called
			visitor->visit(this);
		}
	};

	void ExpressionPrinter::visit(DoubleExpression* de) {
		m_oss << de->m_value;
	}

	void ExpressionPrinter::visit(AdditionExpression* ae) {

		// we want to add braces only if necessary
		bool needBraces = dynamic_cast<SubtractionExpression*>(ae->m_right);

		ae->m_left->Accept(this);
		m_oss << "+";
		if (needBraces) { m_oss << "("; }
		ae->m_right->Accept(this);
		if (needBraces) { m_oss << ")"; }
	}

	void ExpressionPrinter::visit(SubtractionExpression* se) {
		// we want to add braces only if necessary
		bool needBraces = dynamic_cast<SubtractionExpression*>(se->m_right);

		se->m_left->Accept(this);
		m_oss << "-";

		if (needBraces) { m_oss << "("; }
		se->m_right->Accept(this);
		if (needBraces) { m_oss << ")"; }
	}

	void ExpressionEvaluator::visit(DoubleExpression* de) {
		m_result = de->m_value;
	}

	void ExpressionEvaluator::visit(AdditionExpression* ae) {
		// m_result gets overridden every time we call Accept(),
		// so we have to save its value temporarily
		ae->m_left->Accept(this);
		auto temp = m_result;
		ae->m_right->Accept(this);
		m_result += temp;
	}

	void ExpressionEvaluator::visit(SubtractionExpression* se) {
		// m_result gets overridden every time we call Accept(),
		// so we have to save its value temporarily
		se->m_left->Accept(this);
		auto temp = m_result;
		se->m_right->Accept(this);
		m_result = temp - m_result;
	}
}

void DoubleDispatchExample() {
	using namespace DoubleDispatchNamespace;

	AdditionExpression expr{
		new DoubleExpression{1},
		new SubtractionExpression{
			new DoubleExpression(2),
			new DoubleExpression(3)
		}
	};

	// want to print 1+(2-3)=0
	ExpressionPrinter printer{};
	ExpressionEvaluator eval{};
	printer.visit(&expr);
	eval.visit(&expr);
	cout << printer.str() << "=" << eval.m_result;
}