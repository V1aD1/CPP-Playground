#include <iostream>

using namespace std;

/// <summary>
/// Basically, don't stuff your interfaces with too much proposed functionality. 
/// Try to make your interfaces as small as possible so that composition can be used.
/// </summary>

struct IMachine {
	virtual void Print() = 0;
	virtual void Scan() = 0;
	virtual void Fax() = 0;
};

// Okay, this is fine
struct Machine : IMachine {
	virtual void Print() override{}
	virtual void Scan() override{}
	virtual void Fax() override{}
};

// Uh oh, this is NOT fine, printers only print!
struct Printer : IMachine {
	virtual void Print() override{}

	// Even though we wouldn't implement these methods, we ARE
	// basically telling the user that Printer MAYBE does Scan() or Fax()
	// since they have the associated methods?
	virtual void Scan() override
	{
		// I mean what would we even do here?
		// throw an exception? 
		// return nullptr?
		// just do nothing?
	}

	// same goes for this method
	virtual void Fax() override{}
};

// So instead let's create 3 different interfaces
struct IPrinter {
	virtual void Print() = 0;
};

struct IScanner {
	virtual void Scan() = 0;
};

struct IFax {
	virtual void Fax() = 0;
};

// Now THIS is much better, since Scanner only implements Scan()!
struct Scanner : IScanner {
	virtual void Scan() override{}
};

// Better yet, we can use any combination of these interfaces
// to create any kind of object we want!
struct FancyScanner : IScanner, IFax {
	virtual void Scan() override{}
	virtual void Fax() override{}
};