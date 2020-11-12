#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
using namespace std;

struct FluentBuilder;

struct HtmlElement {
	string name, text;
	vector<HtmlElement> elements;
	const size_t indentSize = 2;

	HtmlElement() {}
	HtmlElement(const string& name, const string& text) : name(name), text(text) {}

	string str(int indentLevel = 0) const {
		string i(indentSize * indentLevel, ' ');
		ostringstream oss;
		oss << i << "<" << name << ">" << endl;
		if (text.size() > 0)
			oss << string(indentSize * (indentLevel + 1), ' ') << text << endl;

		for (const auto& e : elements)
			oss << e.str(indentLevel + 1);

		oss << i << "</" << name << ">" << endl;
		return oss.str();
	}

	static FluentBuilder build(string rootName) {
		// don't need to specify name of class that we're building,
		// since it's inferred from the method signature
		return { rootName };
	}
};

/// <summary>
/// This builder is fluent. "Fluent interface" is a OOP design that relies extensively on
/// method chaining. You can even ensure the object is created properly by FORCING the dev
/// to call the correct methods in the correct order, until all required attributes are set
/// </summary>
struct FluentBuilder {
	HtmlElement root;

	FluentBuilder(string rootName) {
		root.name = rootName;
	}

	// Funtion returns reference to FluentBuilder so that 
	// addChild() function can be chained to other FluentBuilder functions
	FluentBuilder& addChild(string childName, string childText) {
		HtmlElement e{ childName, childText };
		root.elements.emplace_back(e);
		return *this;
	}

	string str() const {
		return root.str();
	}

	// calling fluentHtmlBuilder.HtmlElement() returns the root
	operator HtmlElement() const {
		return root;
	}
};

/// <summary>
/// This object can ONLY be created using the build function
/// </summary>
class ForcedHtmlElement {
	// ForcedHtmlElementBuilder must have access to this class' private members
	// in order to properly build an object of this type. In order to give ForcedHtmlElementBuilder
	// access to this class' private members, we make ForcedHtmlElementBuilder a friend
	// of this class
	friend class ForcedHtmlElementBuilder;
	
	string name, text;
	vector<HtmlElement> elements;
	const size_t indentSize = 2;

	ForcedHtmlElement() {}
	ForcedHtmlElement(const string& name, const string& text) : name(name), text(text) {}

public:
	string str(int indentLevel = 0) const {
		string i(indentSize * indentLevel, ' ');
		ostringstream oss;
		oss << i << "<" << name << ">" << endl;
		if (text.size() > 0)
			oss << string(indentSize * (indentLevel + 1), ' ') << text << endl;

		for (const auto& e : elements)
			oss << e.str(indentLevel + 1);

		oss << i << "</" << name << ">" << endl;
		return oss.str();
	}

	static ForcedHtmlElementBuilder build(string rootName) {
		// don't need to specify name of class that we're building,
		// since it's inferred from the method signature
		return { rootName };
	}
};

/// <summary>
/// This builder is the only way to build a ForcedHtmlElement object. It has access
/// to ForcedHtmlElement's private members because it's a friend of ForcedHtmlElement
/// </summary>
struct ForcedHtmlElementBuilder {
	ForcedHtmlElement root;

	ForcedHtmlElementBuilder(string rootName) {
		root.name = rootName;
	}

	ForcedHtmlElementBuilder& addChild(string childName, string childText) {
		ForcedHtmlElement e{ childName, childText };
		root.elements.emplace_back(e);
		return *this;
	}

	string str() const {
		return root.str();
	}

	// calling (object of type ForcedHtmlElementBuilder).ForcedHtmlElement() returns the root
	operator ForcedHtmlElement() const {
		return root;
	}
};

/// <summary>
/// NOTE: None of this works due to circular dependency problems, and forward declarations don't help.
/// Need to split this into .cpp and .h files to get this to work.
/// </summary>
void FluentBuilderExample() {
	FluentBuilder builder1{ "root" };

	// linking works because addChild() returns reference to FluentBuilder
	builder1.addChild("child 1", "child 1 text").addChild("child 2", "child 2 text");
	cout << builder1.str() << endl;

	// we can also get the builder from HtmlElement itself
	auto builder2 = HtmlElement::build("ul").addChild("child 1", "child 1 text");

	// this works because we've overloaded the HtmlElement() operator, which is inferred and used
	// since we've specified that elem is of type HtmlElement
	HtmlElement elem = HtmlElement::build("ul").addChild("child 1", "child 1 text");

	// this does NOT work because ForceHtmlElement's constructors are PRIVATE
	//ForcedHtmlElement fe;

	// we HAVE to do it this way
	ForcedHtmlElement fe = ForcedHtmlElement::build("forced root").addChild("child", "child text");
	cout << fe.str() << endl;

}