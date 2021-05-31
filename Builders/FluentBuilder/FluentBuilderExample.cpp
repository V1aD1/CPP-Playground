#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "ForcedElement.h"
#include "FluentElement.h"
#include "FluentBuilder.h"
#include "ForcedElementBuilder.h"

using namespace std;

/// <summary>
/// A fluent builder is one where the building process is achieved by chaining commands 
/// that always return a reference to the object being built 
/// </summary>
void FluentBuilderExample() {
	cout << "Fluent Builder: " << endl;
	FluentBuilder builder1{ "root" };
	cout << builder1.str() << endl;

	// linking works because addChild() returns reference to FluentBuilder
	builder1.addChild("child 1", "child 1 text").addChild("child 2", "child 2 text");
	cout << builder1.str() << endl;

	// we can also get the builder from FluentElement itself
	auto builder2 = FluentElement::build("ul").addChild("child 1", "child 1 text");
	cout << builder2.str() << endl;

	// this works because we've overloaded the FluentElement() operator, which is inferred and used
	// since we've specified that elem is of type FluentElement
	cout << "Fluent element: " << endl;
	FluentElement elem = FluentElement::build("ul").addChild("child 1", "child 1 text");
	cout << elem.str() << endl;

	// this does NOT work because ForceElement's constructors are PRIVATE
	//ForcedElement fe;

	// we HAVE to do it this way
	cout << "Forced element: " << endl;
	ForcedElement fe = ForcedElement::build("forced root").addChild("child", "child text");
	cout << fe.str() << endl;
}