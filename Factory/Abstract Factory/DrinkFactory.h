#pragma once

#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>
using namespace std;

enum class DrinkType {
	tea,
	coffee
};

class DrinkFactory {
	map<DrinkType, unique_ptr<HotDrinkFactory>> hotFactories;
public:
	DrinkFactory() {
		hotFactories[DrinkType::coffee] = make_unique<CoffeeFactory>();
		hotFactories[DrinkType::tea] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> makeDrink(DrinkType type, int amount) {
		auto drink = hotFactories[type]->make();
		drink->prepare(amount);
		return drink;
	}
};