#pragma once
#include <string>
#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
	// now we can write self instead of PersonAddressBuilder every time
	typedef PersonJobBuilder self;
public:
	PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

	self& at(std::string company) {
		m_person.m_companyName = company;
		return *this;
	}

	self& as(std::string position) {
		m_person.m_position = position;
		return *this;
	}

	self& earning(int annualIncome) {
		m_person.m_annualIncome = annualIncome;
		return *this;
	}
};
