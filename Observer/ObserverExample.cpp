#include <iostream>
#include <boost/signals2.hpp>
#include "Observer.h"
#include "Observable.h"
#include "SaferObservable.h"

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

	struct PersonObserver : Observer<Person> {
		virtual void FieldChanged(Person& source, const string& fieldName) override
		{
			// as you can tell, this REALLY doesn't scale well
			if (fieldName == "age") {
				cout << source.m_name << " is now " << source.getAge() << " years old" << endl;
			}
		}
	};

	template <typename T>
	struct BoostObservable {
		boost::signals2::signal<void(T&, const string&)> fieldChanged;
	};

	class BoostObservablePerson : public BoostObservable<BoostObservablePerson> {
		int m_age;
	public:
		int GetAge() { return m_age; }
		void SetAge(int age){
			if (m_age == age) { return; }
			m_age = age;
			fieldChanged(*this, "age");
		}
	};

	class SafeObservablePerson : public SaferObservable<SafeObservablePerson> {
		int m_age;

	public:
		string m_name;

		SafeObservablePerson(string name, int age) : m_name(name), m_age(age) {}

		int getAge() const { return m_age; }
		void setAge(int age) {
			if (age == m_age) { return; }
			m_age = age;

			OnFieldChanged(*this, "age");
		}
	};

	class SafeObserver : public Observer<SafeObservablePerson> {
		virtual void FieldChanged(SafeObservablePerson& source, const string& fieldName) override
		{
			// as you can tell, this REALLY doesn't scale well
			if (fieldName == "age") {
				cout << source.m_name << " is now " << source.getAge() << " years old" << endl;
			}
		}
	};
}

void ObserverExample() {
	using namespace ObserverNamespace;

	Person person("Vlad", 27);
	PersonObserver observer{};

	person.Subscribe(observer);

	person.setAge(28); // observer will see this and comment on it
	person.setAge(29); // observer will see this and comment on it
	person.Unsubscribe(observer);
	person.setAge(30); // observer will NOT see this since they've unsubscribed
	cout << endl;

	// here is an example of how to use Boost library to build up the Observer pattern
	BoostObservablePerson p2;
	auto conn = p2.fieldChanged.connect(
		// lambda function
		[](BoostObservablePerson& p, const string& fieldName) {
			cout << fieldName << " has changed\n";
		}
	);

	p2.SetAge(20); // the lamdba function above will trigger because the age is changing
	cout << endl;

	// SafeObservable example
	SafeObserver observer2{};
	SafeObservablePerson p3{"Bart", 11};
	p3.Subscribe(observer2);
	p3.setAge(12);
}