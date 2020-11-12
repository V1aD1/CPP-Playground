#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
using namespace std;

struct FluentBuilder;

struct FluentElement {
	string name, text;
	vector<FluentElement> elements;
	const size_t indentSize = 2;

	FluentElement();
	FluentElement(const string& name, const string& text);

	string str(int indentLevel = 0) const;

	static FluentBuilder build(string rootName);
};
