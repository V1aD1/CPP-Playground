#include <iostream>
#include <string>
#include <map>

using namespace std;

class SingletonDatabase {
	map<string, int> capitals;

	// constructor is private to forbid multiple instantiations of this object
	SingletonDatabase() {
		cout << "Initializing db" << endl;
		capitals["Tokyo"] = 33000000;
		capitals["Prague"] = 1700000;
		capitals["Paris"] = 14000000;
	}

public:
	// this is a singleton, we don't want people copying it ever,
	// so we're removing the copy constructor and "=" operator
	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;

	// only way to interact with this object is to use this method
	static SingletonDatabase& get() {
		static SingletonDatabase db;
		return db;
	}

	int getPop(const string& name) {
		return capitals[name];
	}
};

void SingletonExample() {

	// this wouldn't work because we removed "=" operator
	// auto sdb = SingletonDatabase::get()

	auto pop = SingletonDatabase::get().getPop("Paris");
	cout << "Population of Paris is: " << pop << endl;
}