#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum class Colour {red, green, blue};
enum class Size {small, medium, large};

/// <summary>
/// Systems should be open to extension but closed for modification
/// </summary>

struct Product {
	string Name;
	Colour Colour;
	Size Size;
};

struct BadProductFilter {
	vector<Product*> ByColour(vector<Product*> items, Colour colour) {
		vector<Product*> filteredItems;
		for (auto& item : items)
			if (item->Colour == colour)
				filteredItems.push_back(item);
		
		return filteredItems;
	}

	// This is BAD. We may require a filter by name later,
	// which once again copies basically the same method over, and ALSO modifies this class!
	// Even worse, if we require a filter for size AND color then we'll need ANOTHER method. 
	// This architecure does not scale well
	vector<Product*> BySize(vector<Product*> items, Size size) {
		vector<Product*> filteredItems;
		for (auto& item : items)
			if (item->Size == size)
				filteredItems.push_back(item);

		return filteredItems;
	}
};

// Uses the Specification pattern to address the above concerns
template <typename T> 
struct Specification {
	virtual bool IsSatisfied(T* item) const = 0;
};

template <typename T> 
struct Filter {
	virtual vector<T*> filter(vector<T*> items, const Specification<T>& spec) = 0;
};

struct BetterProductFilter: Filter<Product> {
	virtual vector<Product*> filter(vector<Product*> items, const Specification<Product>& spec) override
	{
		vector<Product*> filteredItems;
		for (auto& item : items)
			if (spec.IsSatisfied(item))
				filteredItems.push_back(item);

		return filteredItems;
	}
};

struct ColourSpecification : Specification<Product> {
	
	Colour m_colour;
	
	ColourSpecification(Colour colour) : m_colour(colour) {}

	virtual bool IsSatisfied(Product* item) const override
	{
		return item->Colour == m_colour;
	}
};

struct SizeSpecification : Specification<Product> {
	Size m_size;
	
	SizeSpecification(Size size) : m_size(size) {}

	virtual bool IsSatisfied(Product* item) const override
	{
		return item->Size == m_size;
	}

};

template <typename T> 
struct AndSpecification : Specification<T> {
	vector<Specification<T>*> m_specs;

	AndSpecification(vector<Specification<T>*> specs): m_specs(specs){}

	virtual bool IsSatisfied(T* item) const override
	{
		for (auto& spec : m_specs)
			if (spec->IsSatisfied(item) == false)
				return false;
		return true;
	}
};

void OpenClosedPrinciple() {
	Product apple{"Apple", Colour::green, Size::small};
	Product sofa{ "Sofa", Colour::blue, Size::medium };
	Product car{ "Car", Colour::red, Size::large };

	vector<Product*> items{ &apple, &sofa, &car };

	BetterProductFilter pf;
	
	cout << "Green items:" << endl;
	auto greenItems = pf.filter(items, ColourSpecification(Colour::green));
	for(auto& item : greenItems)
		cout << item->Name << endl;

	cout << "Red and large items:" << endl;
	vector<Specification<Product>*> specs = { &ColourSpecification(Colour::red), &SizeSpecification(Size::large) };
	AndSpecification<Product> redAndLarge(specs);
	auto redAndLargeItems = pf.filter(items, redAndLarge);
	for (auto& item : redAndLargeItems)
		cout << item->Name << endl;
}