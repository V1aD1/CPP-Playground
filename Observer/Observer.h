#pragma once
#include <string>

using namespace std;

template<typename T>
class Observer
{
	virtual void FieldChanged(T& source, string fieldName) = 0;
};

