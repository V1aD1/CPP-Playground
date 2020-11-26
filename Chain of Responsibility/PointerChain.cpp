#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace PointerChain {
	struct Creature {
		string m_name;
		int m_attack, m_defence;

		Creature(const string& name, int attack, int defence) : m_name(name), m_attack(attack), m_defence(defence) {}

		friend ostream& operator<<(ostream& os, const Creature& creature) {
			os << "Name: " << creature.m_name << " Attack: " << creature.m_attack << " Defence: " << creature.m_defence;
			return os;
		}
	};

	// these objects will be linkedin together in a singly-linked list
	class CreatureModifier {
		CreatureModifier* m_next{ nullptr };
	protected:
		Creature& m_creature;
	public:
		CreatureModifier(Creature& creature) : m_creature(creature) {}
		
		void add(CreatureModifier* mod) {
			if (m_next)
				m_next->add(mod);
			else
				m_next = mod;
		}
	
		virtual void handle() {
			if (m_next) m_next->handle();
		}

	};

	class DoubleDamageModifier : public CreatureModifier {
	public:
		DoubleDamageModifier(Creature& creature): CreatureModifier(creature){}
		
		void handle() override {
			m_creature.m_attack *= 2;

			// calling base class handle()
			CreatureModifier::handle();
		}
	};

	class IncreaseDefenceModifier : public CreatureModifier {
	public:
		IncreaseDefenceModifier(Creature& creature): CreatureModifier(creature){}

		void handle() override {
			m_creature.m_defence++;
			
			// calling base class handle()
			CreatureModifier::handle();
		}
	};
}

void PointerChainExample() {
	using namespace PointerChain;

	Creature goblin{ "Goblin", 1, 1 };
	CreatureModifier root{ goblin };
	DoubleDamageModifier dmgMod{ goblin };
	IncreaseDefenceModifier defMod{ goblin };

	root.add(&dmgMod);
	root.add(&defMod);

	root.handle();

	cout << goblin << endl;
}