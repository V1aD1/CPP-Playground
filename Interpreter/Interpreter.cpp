#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

using namespace std;

namespace Interpreter {
	struct Token {
		enum Type {integer, plus, minus, lparen, rparen} m_type;
		string m_text;

		Token(Type type, const string& text) : m_type(type), m_text(text) {}
		
		friend ostream& operator<<(ostream& os, const Token& token) {
			os << "'" << token.m_text << "'";
			return os;
		}
	};

	vector<Token> lex(const string& input) {
		vector<Token> result;

		for (int i = 0; i < input.size(); i++) {
			switch (input[i]) {
			case '(':
				result.push_back(Token{ Token::Type::lparen, "(" });
				break;
			case ')':
				result.push_back(Token{ Token::Type::rparen, ")" });
				break;
			case '+':
				result.push_back(Token{ Token::Type::plus, "+" });
				break;
			case '-':
				result.push_back(Token{ Token::Type::minus, "-" });
				break;
			case ' ':
				break;
			
			// this is where we handle numbers
			default:
				ostringstream buffer;
				if (isdigit(input[i])) {
					buffer << input[i];
					for (int j = i+1; j < input.size(); ++j) {
						if (isdigit(input[j])) {
							buffer << input[j];
							++i;
						}
						else{
							result.push_back(Token{ Token::Type::integer, buffer.str() });
							break;
						}
					}
				}
				break;
			}
		}
		return result;
	}

	struct Element {
		virtual int eval() const = 0;
	};

	struct Integer :Element {
		int m_value;

		Integer(int value) : m_value(value){}

		virtual int eval() const override
		{
			return m_value;
		}

	};

	struct BinaryOperation :Element {
		enum Type {addition, subtraction} m_type;
		shared_ptr<Element> m_left, m_right;
		bool m_hasLeft;

		virtual int eval() const override
		{
			switch (m_type) {
			case Type::addition:
				return m_left->eval() + m_right->eval();
				break;
			case Type::subtraction:
				return m_left->eval() - m_right->eval();
				break;
			}
		}

	};

	shared_ptr<Element> parse(const vector<Token>& tokens) {
		auto retVal = make_shared<BinaryOperation>();

		for (int i = 0; i < tokens.size(); ++i) {
			switch (tokens[i].m_type) {
			case Token::integer:
				// {} scope necessary in this case statement because 
				// we create a new variable (val) within this case statement
				{
					int val = boost::lexical_cast<int>(tokens[i].m_text);
					if (!retVal->m_hasLeft) {
						retVal->m_left = make_shared<Integer>(val);
						retVal->m_hasLeft = true;
					}
					retVal->m_right = make_shared<Integer>(val);
				}
				break;
			case Token::plus:
				retVal->m_type = BinaryOperation::addition;
				break;
			case Token::minus:
				retVal->m_type = BinaryOperation::subtraction;
				break;
			case Token::lparen:
				int j = i;
				for (; j < tokens.size(); ++j) {
					if (tokens[j].m_type == Token::rparen) {
						break;
					}
				}

				vector<Token> subExpression(&tokens[i + 1], &tokens[j]);

				// recursive call
				auto element = parse(subExpression);
				if (!retVal->m_hasLeft) {
					retVal->m_left = element;
					retVal->m_hasLeft = true;
				}

				else {
					retVal->m_right = element;
				}
				i = j;
				break;
			}
		}

		return retVal;
	}
}

void InterpreterExample() {
	using namespace Interpreter;

	string expression = "(11 + 23) - (34 + 4)";
	auto tokens = lex(expression);

	for (auto& token : tokens) {
		cout << token << ' ';
	}

	cout << endl;

	auto parsedExpr = parse(tokens);

	cout << expression << " = " << parsedExpr->eval();
}