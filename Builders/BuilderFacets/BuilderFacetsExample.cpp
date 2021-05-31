#include <iostream>
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

/// <summary>
/// Different facets of an object can be built with different builders working in tandem
/// via a base class. You can 
/// </summary>
void BuilderFacetsExample() {
	Person p = Person::create().lives().at("1234 Dundas")
									   .withPostalCode("A7S 8T8")
									   .in("Toronto")
							   .works().at("Capybara Games")
									   .as("Gameplay Programmer")
									   .earning(6e5);
	std::cout << p << std::endl;
}