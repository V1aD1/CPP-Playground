#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product {
	string Name;
	Color Color;
	Size size;
};

struct ProductFilter {
	vector<Product*> ByColor(vector<Product*> items, Color color) {
		vector<Product*> filteredItems;
		for (auto&
			item : items)
			if (item->Color == color)
				filteredItems.push_back(item);
		
		return filteredItems;
	}
};

void OpenClosedPrinciple() {
	Product apple{"Apple", Color::green, Size::small};
	Product sofa{ "Sofa", Color::blue, Size::medium };
	Product car{ "Car", Color::red, Size::large };

	vector<Product*> items{ &apple, &sofa, &car };

	ProductFilter pf;

	auto greenItems = pf.ByColor(items, Color::green);
	
	for(auto& item : greenItems)
		std::cout << item->Name << std::endl;
}