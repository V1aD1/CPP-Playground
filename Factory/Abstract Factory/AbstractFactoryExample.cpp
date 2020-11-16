#include <iostream>
#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

using namespace std;

void AbstractFactoryExample() {
	auto df = DrinkFactory();
	auto tea = df.makeDrink(DrinkType::tea, 200);
	auto coffee = df.makeDrink(DrinkType::coffee, 100);
}