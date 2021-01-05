#pragma once

#include <iostream>

/// <summary>
/// Pimpl stands for "pointer to implementation", and it's a way to obfuscate the implementation
/// details of your class. When working in cpp, you have to provide the user of your API with 
/// the header files, which contain all function definitions, regardless of whether they're private or not.
/// This may reveal implementation details that you don't want to reveal. 
/// 
/// Luckily, clients do NOT have access to cpp files. 
/// 
/// By implementing all functionality behind an opaque pointer to an implementation, you are able to hide
/// the innerworkings of your implementation from the users of you API.
/// </summary>
class Pimpl
{
public:
	class PimplImpl;
	PimplImpl* m_impl;
	int m_someInfo{ 0 };

	Pimpl();

	~Pimpl();

	// this method may have to call some secret function like recordKeyStrokes() or something,
	// but instead of recordKeyStrokes() being detailed here as a private function (the function
	// definition of which would be visible to the user of the API), we just implement
	// recordKeyStrokes() in the corresponding cpp file, as a member of PimplImpl
	void SomePublicMethod();
};

