#include <iostream>
#include <string>

using namespace std;

struct Address {
	string m_street, m_city;
	int m_suite;

	Address(const string& street, const string& city, int suite): m_street(street), m_city(city), m_suite(suite){}
	
	// copy constructor
	Address(const Address& other): m_street(other.m_street), m_city(other.m_city), m_suite(other.m_suite){}
	
	friend ostream& operator<<(ostream& os, const Address& address) {
		os << address.m_street << ' ' << address.m_city << ' ' << address.m_suite;
		return os;
	}
};

struct Contact {
	string m_name;
	Address* m_address;

	Contact(const string& name, Address* address): m_name(name), m_address(address){}
	
	// copy constructor
	Contact(const Contact& other): m_name(other.m_name), m_address(new Address{*other.m_address}){}
	
	friend ostream& operator<<(ostream& os, const Contact& contact) {
		os << contact.m_name << ' ' << *contact.m_address;
		return os;
	}
};

void PrototypeExample() {
	Contact john{ "John Doe", new Address{"2167 Something Drive", "Toronto", 14} };
	Contact jane{ john };
	jane.m_name = "Jane Smith";
	
	//this change here would also change john's address, if not for the copy constructor!
	jane.m_address->m_suite = 17;

	cout << john << endl << jane << endl;

}