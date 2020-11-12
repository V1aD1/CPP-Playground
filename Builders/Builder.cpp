#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
using namespace std;

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
};

/// <summary>
/// Instead of constructing an object manually, every time, use a specialized component
/// that constructs the object for you in a simpler, more concise way
/// </summary>
struct HtmlBuilder {
	HtmlElement root;

	HtmlBuilder(string rootName) {
		root.name = rootName;
	}

	void addChild(string childName, string childText) {
		HtmlElement e{ childName, childText };
		root.elements.emplace_back(e);
	}

	string str() const{
		return root.str();
	}
};

void Builder() {
	HtmlBuilder builder{ "root" };
	builder.addChild("child 1", "child 1 text");
	builder.addChild("child 2", "child 2 text");
	cout << builder.str() << endl;
}