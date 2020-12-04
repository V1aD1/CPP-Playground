#include <iostream>
#include "Observer.h"
#include "Observable.h"

namespace ObserverNamespace {
	class Person : public Observable<Person>{
		int m_age;

	public:
		string m_name;

		Person(string name, int age) : m_name(name), m_age(age) {}

		int getAge() const { return m_age; }
		void setAge(int age) { 
			if (age == m_age) { return; }
			m_age = age;

			OnFieldChanged(*this, "age");
		}
	};

	struct ConsolePersonObserver : Observer<Person> {
		virtual void FieldChanged(Person& source, const string& fieldName) override
		{
			if (fieldName == "age") {
				cout << source.m_name << " is now " << source.getAge() << " years old" << endl;
			}
		}
	};
}

void ObserverExample() {
	using namespace ObserverNamespace;

	Person person("Vlad", 27);
	ConsolePersonObserver observer{};

	person.Subscribe(observer);

	person.setAge(28); // observer will see this and comment on it
	person.setAge(29); // observer will see this and comment on it
	person.Unsubscribe(observer);
	person.setAge(30); // observer will NOT see this since they've unsubscribed
}