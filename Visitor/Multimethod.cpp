#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <typeindex>
#include <map>

using namespace std;

namespace Multimethod {
	struct GameObject;
	void collide(GameObject& first, GameObject& second);

	struct GameObject {
		virtual type_index type() const = 0;

		virtual void collide(GameObject& other) {
			Multimethod::collide(*this, other);
		}
	};

	// Uses CRTP: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
	template<typename T>
	struct GameObjectImpl : GameObject {
		type_index type() const override {
			return typeid(T);
		}
	};

	struct Planet : GameObjectImpl<Planet> {};
	struct Asteroid : GameObjectImpl<Asteroid> {};
	struct Spaceship : GameObjectImpl<Spaceship> {};

	void SpaceshipPlanetMsg() { cout << "spaceship lands on a planet\n"; }
	void AsteroidPlanetMsg() { cout << "asteroid burns up in the atmosphere\n"; }
	void AsteroidSpaceshipMsg() { cout << "asteroid hits and destroys spaceship\n"; }

	map<pair<type_index, type_index>, void(*)(void)> outcomes{
		{{typeid(Spaceship), typeid(Planet)}, SpaceshipPlanetMsg},
		{{typeid(Asteroid), typeid(Planet)}, AsteroidPlanetMsg},
		{{typeid(Asteroid), typeid(Spaceship)}, AsteroidSpaceshipMsg}
	};

	void collide(GameObject& first, GameObject& second) {
		auto test = { first.type(), second.type() };
		auto it = outcomes.find({ first.type(), second.type() });
		if (it == outcomes.end()) {
			// swapping values to make a new pair in order to check equality
			it = outcomes.find({ second.type(), first.type() });
			if (it == outcomes.end()) {
				cout << "objects pass each other harmlessly\n";
				return;
			}
		}

		// calls function from outcomes dict (values in outcomes dict are functions)
		it->second();
	}
}

void MultimethodExample() {
	using namespace Multimethod;

	Asteroid asteroid;
	Planet planet;
	Spaceship ship;

	collide(planet, asteroid);
	collide(planet, ship);
	collide(asteroid, ship);
	collide(planet, planet);
}