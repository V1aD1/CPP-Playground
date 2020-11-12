#include "ForcedElementBuilder.h"

ForcedElementBuilder::ForcedElementBuilder(string rootName) {
	root.name = rootName;
}

ForcedElementBuilder& ForcedElementBuilder::addChild(string childName, string childText) {
	ForcedElement e{ childName, childText };
	root.elements.emplace_back(e);
	return *this;
}

string ForcedElementBuilder::str() const {
	return root.str();
}

// calling (object of type ForcedElementBuilder).ForcedElement() returns the root
ForcedElementBuilder::operator ForcedElement() const {
	return root;
}