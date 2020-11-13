#pragma once
#include "Person.h"

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase {
protected:
	Person& m_person;
public:
	PersonBuilderBase(Person& person);
	operator Person() const;
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
public:
	PersonBuilder();
private:
	Person m_p;
};

