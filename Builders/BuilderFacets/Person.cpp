#include "iostream"
#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create()
{
	return PersonBuilder();
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
	os << "address: " << person.m_streetAddress << ", " << person.m_postalCode << ", " << person.m_city << " working at " << person.m_companyName << " earning " << person.m_annualIncome << " per year.";
	return os;
}
