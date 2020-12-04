#include <iostream>
#include "Observer.h"

namespace ObserverNamespace {
	class Person {
		int m_age;

	public:
		string m_name;

		Person(string name, int age) : m_name(name), m_age(age) {}

		int getAge() const { return m_age; }
		void setAge(int age) { m_age = age; }
	};

	struct ConsolePersonObserver : Observer<Person> {
		virtual void FieldChanged(Person& source, string fieldName) override
		{
			if (fieldName == "age") {
				cout << source.m_name << " is now " << source.getAge() << " years old" << endl;
			}
		}
	};
}

void ObserverExample() {
	using namespace ObserverNamespace;
}