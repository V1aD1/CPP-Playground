#pragma once
#include <iostream>
using namespace std;

struct HotDrink {
	virtual ~HotDrink() = default;
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
	virtual void prepare(int volume) override {
		cout << "Boil " << volume << "ml of water, put tea bag in it, add lemon." << endl;
	}
};

struct Coffee : HotDrink {
	virtual void prepare(int volume) override {
		cout << "Boil " << volume << "ml of water, put coffee powder, add cream." << endl;
	}
};