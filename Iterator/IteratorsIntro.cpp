#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


void IteratorsIntroExample() {
	vector<string> names{ "john", "jane", "jill", "jack" };
	vector<string>::iterator it = names.begin(); // can also use begin(names)

	// it is kindof like a pointer, so we need to dereference it to access its value
	cout << "first name is: " << *it << endl;
	
	// advances it to next element in vector (jane)
	++it; 

	// iterator can be used to modify element itself
	it->append(string(" doe")); 
	cout << "second name is: " << *it << endl;

	// names.end() returns pointer to memory location AFTER end of vector
	while (++it != names.end()) {
		cout << "another name: " << *it << endl;
	}

	// we ALSO have reverse iterators, and range based for loops
	// rbegin() points to the end of the collection, rend() points to the beginning!
	// yes, even when iterating backwards, we still ++ the iterator!
	for (auto ri = rbegin(names); ri != rend(names); ++ri) {
		cout << *ri;
		if (ri + 1 != rend(names)) {
			// add a comma when necessary
			cout << " ,";
		}
	}

	cout << endl;

	// we ALSO have const iterators, that don't allow you to modify the collection
	// in the future it's best to use auto here
	vector<string>::const_reverse_iterator jack = crbegin(names);
	
	// obvi wouldn't work
	//*jack += string(" black");

	// auto would do a complete copy (inefficient)
	// auto& would reference, which would be better but woudln't work for R values
	// auto&& works for all cases, and for both R and L values, so always use it
	for (auto&& name : names) {
		cout << "name: " << name << endl;
	}
}