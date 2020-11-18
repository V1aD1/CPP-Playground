// A multiton is a variation of a singleton, but instead of only allowing
// 1 instance of an object, it RESTRICTS the number of objects, depending
// on some keys

#include <map>
#include <iostream>
#include <cassert>
using namespace std;

enum class Importance {
	primary,
	secondary
};

template <typename T, typename Key = std::string>
class Multiton {
public:
	static shared_ptr<T> get(const Key& key) {
		// the ability to declare a variable in if() statement itself was added in C++17
		if (const auto it = instances.find(key); it != instances.end())
			return it->second;

		// ok, no object for that particular key exists, so create it,
		// add it to instance map, and then return it
		auto instance = make_shared<T>();
		instances[key] = instance;
		return instance;
	}

	// multitons, like singletons, aren't supposed to get manually instantiated
	// only static methods should be used when interacting with multitons
	Multiton(Multiton const&) = delete;
	void operator=(Multiton const&) = delete;


private:
	static map<Key, shared_ptr<T>> instances;
};

// this just initializes the map so that we can use it
template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class SomeClass {
public:
	SomeClass(){
		++SomeClass::totalInstanceCount;
		cout << "A total of " << SomeClass::totalInstanceCount 
			<< " instances created so far" << endl;
	}
	static int totalInstanceCount;
};

int SomeClass::totalInstanceCount = 0;

void MultitonExample() {
	typedef Multiton<SomeClass, Importance> mt;

	auto primary = mt::get(Importance::primary);
	auto secondary = mt::get(Importance::secondary);

	// this should not result in another instantiation of SomeClass,
	// since we already have a value for Importance::secondary
	auto anotherSecondary = mt::get(Importance::secondary);
	assert(SomeClass::totalInstanceCount == 2);
}