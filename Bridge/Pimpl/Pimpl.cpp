#include "Pimpl.h"

using namespace std;

class Pimpl::PimplImpl {
public:
	void SomePublicMethod(Pimpl* p);
private:
	void recordKeyStrokes(Pimpl* p);
};

Pimpl::Pimpl(): m_impl(new PimplImpl){}

// remember that pointers should always be handled in order to
// avoid memory leaks!
Pimpl::~Pimpl()
{
	delete m_impl;
}

void Pimpl::SomePublicMethod()
{
	m_impl->SomePublicMethod(this);
}

void Pimpl::PimplImpl::SomePublicMethod(Pimpl* p)
{
	// the consumer of the API has no idea about this method!
	recordKeyStrokes(p);
	
	// do other stuff...
}

// the consumer of the API has no idea about this method!
void Pimpl::PimplImpl::recordKeyStrokes(Pimpl* p)
{
	cout << "Recording key strokes!" << endl;
}

void PimplExample() {
	Pimpl x;
	x.SomePublicMethod();
}