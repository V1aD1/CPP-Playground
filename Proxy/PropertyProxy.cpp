#include <iostream>

using namespace std;

namespace PropertyProxy {
	
	template <typename T> struct LoggedProperty {
		LoggedProperty(T value) {
			*this = value;
		}

		operator T() {
			return m_value;
		}

		T operator=(T newValue) {
			cout << "Assignment!" << endl;
			return m_value = newValue;
		}
	
	private:
		T m_value;
	};
	
	struct Creature {
		LoggedProperty<int> strength{ 0 };
		LoggedProperty<int> agility{ 0 };
	};
}

void PropertyProxyExample() {
	using namespace PropertyProxy;

	// all of these operations will call the = operator
	Creature c;
	c.strength = 10;
	int x = c.agility;
}