#include "ForcedElement.h"
#include "ForcedElementBuilder.h"

ForcedElement::ForcedElement() {}
ForcedElement::ForcedElement(const string& name, const string& text) : name(name), text(text) {}

string ForcedElement::str(int indentLevel) const {
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

ForcedElementBuilder ForcedElement::build(string rootName) {
	// don't need to specify name of class that we're building,
	// since it's inferred from the method signature
	return { rootName };
}
