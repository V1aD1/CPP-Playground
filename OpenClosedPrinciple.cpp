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
	// which once again copies basically the same method over.
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
template <typename T> struct Specification {
	virtual bool IsSatisfied(T* item) = 0;
};

template <typename T> struct Filter {
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterProductFilter: Filter<Product> {
	virtual vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override
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

	virtual bool IsSatisfied(Product* item) override
	{
		return item->Colour == m_colour;
	}
};

void OpenClosedPrinciple() {
	Product apple{"Apple", Colour::green, Size::small};
	Product sofa{ "Sofa", Colour::blue, Size::medium };
	Product car{ "Car", Colour::red, Size::large };

	vector<Product*> items{ &apple, &sofa, &car };

	ColourSpecification colSpec = ColourSpecification(Colour::red);
	BetterProductFilter pf;

	auto greenItems = pf.filter(items, colSpec);
	
	for(auto& item : greenItems)
		std::cout << item->Name << std::endl;
}