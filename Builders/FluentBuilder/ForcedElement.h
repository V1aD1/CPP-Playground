#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
using namespace std;

struct ForcedElementBuilder;

/// <summary>
/// This object can ONLY be created using the build function
/// </summary>
class ForcedElement {
	// ForcedElementBuilder must have access to this class' private members
	// in order to properly build an object of this type. In order to give ForcedElementBuilder
	// access to this class' private members, we make ForcedElementBuilder a friend
	// of this class
	friend struct ForcedElementBuilder;

	string name, text;
	vector<ForcedElement> elements;
	const size_t indentSize = 2;

	ForcedElement();
	ForcedElement(const string& name, const string& text);

public:
	string str(int indentLevel = 0) const;

	static ForcedElementBuilder build(string rootName);
};