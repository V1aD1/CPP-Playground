#include "FluentBuilder.h"

FluentBuilder::FluentBuilder(string rootName) {
	root.name = rootName;
}

FluentBuilder& FluentBuilder::addChild(string childName, string childText) {
	FluentElement e{ childName, childText };
	root.elements.emplace_back(e);
	return *this;
}

string FluentBuilder::str() const {
	return root.str(0);
}

FluentBuilder::operator FluentElement() const
{
	return root;
}