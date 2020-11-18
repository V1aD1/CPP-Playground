#include <iostream>
#include <string>

using namespace std;

struct Address {
	string m_street, m_city;
	int m_suite;

	Address(const string& street, const string& city, int suite): m_street(street), m_city(city), m_suite(suite){}
	friend ostream& operator<<(ostream& os, const Address& address) {
		os << address.m_street << ' ' << address.m_city << ' ' << address.m_suite;
		return os;
	}
};

struct Contact {
	string m_name;
	Address m_address;

	Contact(const string& name, const Address& address): m_name(name), m_address(address){}
	friend ostream& operator<<(ostream& os, const Contact& contact) {
		os << contact.m_name << ' ' << contact.m_address;
		return os;
	}
};

void PrototypeExample() {
	Contact john{ "John Doe", Address{"2167 Something Drive", "Toronto", 14} };
	Contact jane{ "Jane Smith", Address{"2167 Something Drive", "Toronto", 17} };

	cout << john << endl << jane << endl;

}