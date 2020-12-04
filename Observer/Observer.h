#pragma once
#include <string>

using namespace std;

template<typename T>
class Observer
{
public:
	virtual void FieldChanged(T& source, const string& fieldName) = 0;
};

