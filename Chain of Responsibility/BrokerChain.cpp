#include <string>
#include <iostream>
#include <sstream>
#include <boost/signals2.hpp>

using namespace boost;
using namespace std;

namespace BrokerChain {
	
	struct Query {
		string m_creatureName;
		enum Argument{attack, defence} m_argument;
		int m_result;

		Query(const string& creatureName, Argument argument, int result) :
			m_argument(argument), m_result(result), m_creatureName(creatureName) {}
	};

	// mediator pattern
	struct Game {
		// signals are created by first specifying a return type and function signature (as template parameters)
		// of the functions that will connect to the signal. Once all functions are connected to a signal,
		// all functions can be run, in sequential order, by simply calling the signal()
		// in our case, this happens in the getAttack() method below
		boost::signals2::signal<void(Query&)> queries;
	};

	struct Creature {
		Game& m_game;
		int m_attack;
		string m_name;
	public:
		Creature(Game& game, int attack, const string& name) : 
			m_game(game), m_attack(attack), m_name(name) {}
		
		int getAttack() const {
			Query q{ m_name, Query::Argument::attack, m_attack };
			
			// calling every method connected with the signal and passing in q as the parameter
			m_game.queries(q);
			return q.m_result;
		}

		friend ostream& operator<<(ostream& os, const Creature& creature) {
			os << "Name: " << creature.m_name << " Attack: " << creature.getAttack();
			return os;
		}
	};

	class CreatureModifier {
		Game& m_game;
		Creature& m_creature;
	public:
		CreatureModifier(Game& game, Creature& creature) : m_game(game), m_creature(creature) {}
		virtual ~CreatureModifier() = default;
	};

	class DoubleAttackModifier : public CreatureModifier {
		boost::signals2::connection m_conn;
	public:
		DoubleAttackModifier(Game& game, Creature& creature): CreatureModifier(game, creature)
		{
			// passing lambda function, which looks over queries to determine
			// if modifier should be applied to specified creature
			m_conn = game.queries.connect([&](Query& q)
			{
				if (q.m_creatureName == creature.m_name &&
					q.m_argument == Query::Argument::attack)
				{
					q.m_result *= 2;
				}
			});
		}

		~DoubleAttackModifier() { m_conn.disconnect(); }
	};
}

void BrokerChainExample() {
	using namespace BrokerChain;

	Game game;
	Creature strongGoblin{ game, 2, "Strong Goblin" };

	cout << strongGoblin << endl;
	{
		// The modifier is only applied when in active,
		// and it unsubscribes once we leave this scope
		DoubleAttackModifier dmg{ game, strongGoblin };
		cout << strongGoblin << endl;
	}

	cout << strongGoblin << endl;
}