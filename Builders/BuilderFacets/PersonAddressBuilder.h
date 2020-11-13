#pragma once
#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase
{
	// now we can write self instead of PersonAddressBuilder every time
	typedef PersonAddressBuilder self;
public:
	PersonAddressBuilder(Person &person) : PersonBuilderBase(person){}
	
	self& at(std::string streetAddress) {
		m_person.m_streetAddress = streetAddress;
		return *this;
	}

	self& withPostalCode(std::string postalCode) {
		m_person.m_postalCode = postalCode;
		return *this;
	}

	self& in(std::string city) {
		m_person.m_city = city;
		return *this;
	}
};

