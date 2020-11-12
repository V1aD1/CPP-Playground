#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "ForcedElement.h"

using namespace std;

/// <summary>
/// This builder is the only way to build a ForcedElement object. It has access
/// to ForcedElement's private members because it's a friend of ForcedElement
/// </summary>
struct ForcedElementBuilder {
	ForcedElement root;

	ForcedElementBuilder(string rootName);

	ForcedElementBuilder& addChild(string childName, string childText);

	string str() const;

	// calling (object of type ForcedElementBuilder).ForcedElement() returns the root
	operator ForcedElement() const;
};