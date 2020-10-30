#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
using namespace std;

/// <summary>
/// A. High-level modules should not depend on low-level modules
///	   Instead both should depend on abstractions
/// B. Abstractions should not depend on details.
///	   Instead details should depend on abstractions
/// </summary>

enum class Relationship {
	parent,
	child, 
	sibling
};

struct Person {
	string name;
};

// Low-level module
struct Relationships {
	vector<tuple<Person, Relationship, Person>> relations;

	void AddParentChildRelationship(Person& parent, Person& child) {
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });
	}
};

// High-level module
struct BadResearch {
	// This violates A. because it depends on a low-level module instead of an abstraction
	BadResearch(Relationships& relationships, const string& name) {

		// This violates B. because it depends on the DETAILS of the implementation
		// I mean, what if relations member becomes private in the future??
		auto& relations = relationships.relations;
		
		// some wacky C++17 feature
		for (auto&& [first, rel, second] : relations) {
			if (first.name == name && rel == Relationship::parent) {
				cout << name << " has a child called " << second.name << endl;
			}
		}
	}
};

// Instead, let's make an abstraction
struct IRelationshipBrowser {
	virtual vector<Person> FindAllChildrenOf(const string& name) = 0;
};

// Low-level module BUT it relies on abstraction
struct GoodRelationships: IRelationshipBrowser {
	vector<tuple<Person, Relationship, Person>> relations;

	void AddParentChildRelationship(Person& parent, Person& child) {
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });
	}

	vector<Person> FindAllChildrenOf(const string& name) override
	{
		vector<Person> children;
		for (auto&& [first, rel, second] : relations) {
			if (first.name == name && rel == Relationship::parent)
				children.push_back(second);
		}

		return children;
	}
};

// High-level module BUT it relies on abstraction, not a low-level module
struct GoodResearch {
	GoodResearch(IRelationshipBrowser& relationshipBrowser, const string& name) {
		// some wacky C++17 feature
		for (auto&& child : relationshipBrowser.FindAllChildrenOf(name)) {
			cout << name << " has a child called " << child .name << endl;
		}
	}
};

void DependencyInversionPrinciple() {
	Person parent{ "Vlad" };
	Person child1{ "Lilith" }, child2{"Gan"};

	// weird way to instantiate a struct but whatever
	Relationships relationships;
	relationships.AddParentChildRelationship(parent, child1);
	relationships.AddParentChildRelationship(parent, child2);

	// This will work, sure, but it isn't flexible at ALL
	BadResearch research{relationships, "Vlad"};

	// Let's use the properly designed objects
	GoodRelationships goodRelationships;
	goodRelationships.AddParentChildRelationship(parent, child1);
	goodRelationships.AddParentChildRelationship(parent, child2);

	// This is so much nicer!
	GoodResearch goodResearch(goodRelationships, "Vlad" );
}