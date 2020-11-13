#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonBuilderBase::PersonBuilderBase(Person& person) : m_person(person)
{
}

PersonBuilderBase::operator Person() const
{
	return std::move(m_person);
}

PersonAddressBuilder PersonBuilderBase::lives() const
{
	return PersonAddressBuilder(m_person);
}

PersonJobBuilder PersonBuilderBase::works() const
{
	return PersonJobBuilder(m_person);
}

PersonBuilder::PersonBuilder() : PersonBuilderBase(m_p)
{
}
