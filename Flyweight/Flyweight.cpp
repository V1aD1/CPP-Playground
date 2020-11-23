#include <string>
#include <iostream>
#include <sstream>
#include <boost/bimap.hpp>

using namespace std;

namespace Flyweight {
	struct User {
		int m_firstName;
		int m_lastName;

		User(const string& firstName, const string& lastName) {
			m_firstName = add(firstName);
			m_lastName = add(lastName);
		}

		const string& GetFirstName() const {
			return names.left.find(m_firstName)->second;
		}
		const string& GetLastName() const {
			return names.left.find(m_lastName)->second;
		}

	protected:
		// many users will share the same names, so let's store 
		// only one instance of every name, and "point" to them 
		// in the User object, in order to save memory
		static boost::bimap<int, string> names;
		static int seed;

		static int add(const string& s) {
			auto it = names.right.find(s);
			
			// name not stored in db yet, so store it
			if (it == names.right.end()) {
				int id = ++seed;
				names.insert({ seed, s });
				return id;
			}

			// name already stored, so return its corresponding key value
			return it->second;
		}
	};

	int User::seed{ 0 };
	boost::bimap<int, string> User::names{};
	ostream& operator<<(ostream& os, const User& user) {
		os << "First name: " << user.GetFirstName() << ", located at: " << user.m_firstName
			<< ", Last Name: " << user.GetLastName() << ", located at: " << user.m_lastName << endl;
		return os;
	}
}

void FlyweightExample() {
	using namespace Flyweight;

	User a{ "John", "Smith" };
	User b{ "John", "Doe" };
	User c{ "Paul", "Doe" };

	cout << a << b << c << endl;
}