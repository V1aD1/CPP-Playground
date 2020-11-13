#pragma once
#include <string>

class PersonBuilder;

class Person
{
	std::string m_streetAddress, m_postalCode, m_city;
	std::string m_companyName, m_position;
	int m_annualIncome{ 0 };

public:
	static PersonBuilder create();
	friend std::ostream &operator<<(std::ostream& os, const Person& person);

	friend class PersonBuilder;
	friend class PersonJobBuilder;
	friend class PersonAddressBuilder;
};

