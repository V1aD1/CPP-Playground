#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "FluentElement.h"

using namespace std;

/// <summary>
/// This builder is fluent. "Fluent interface" is a OOP design that relies extensively on
/// method chaining. You can even ensure the object is created properly by FORCING the dev
/// to call the correct methods in the correct order, until all required attributes are set (check out Builder Facets)
/// </summary>
struct FluentBuilder {
	FluentElement root;

	FluentBuilder(string rootName);

	// Funtion returns reference to FluentBuilder so that 
	// addChild() function can be chained to other FluentBuilder functions
	FluentBuilder& addChild(string childName, string childText);

	string str() const;

	// calling fluentHtmlBuilder.FluentElement() returns the root
	operator FluentElement() const;
};