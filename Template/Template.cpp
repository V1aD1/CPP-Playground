#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace TemplateNamespace {
	class Game {
	public:
		Game(int numPlayers) : m_numPlayers(numPlayers) {}

		void run() {

			// most of these methods are pure virtual, but subclasses will implement them. THIS is the template pattern.
			Start();
			while (!HaveWinner()) {
				TakeTurn();
			}
			cout << "Player " << GetWinner() << " wins!!" << endl;
		}

	protected:
		int m_numPlayers;
		virtual void Start() = 0;
		virtual bool HaveWinner() = 0;
		virtual void TakeTurn() = 0;
		virtual int GetWinner() = 0;

	};

	class Chess : public Game {
	public:
		// Chess is a 2 player game
		Chess(int numTurns) : Game(2), m_numOfTurns(numTurns) {}
	protected:
		virtual void Start() override
		{
			cout << "Starting a game of chess!" << endl;
		}
		virtual bool HaveWinner() override
		{
			if (m_currentTurn == m_numOfTurns) { return true; }
			return false;
		}
		virtual void TakeTurn() override
		{
			cout << "Player " << m_currentPlayer << " has completed their turn." << endl;
			m_currentTurn++;

			// game will end once total number of turns are taken
			m_currentPlayer = (m_currentPlayer + 1) % m_numPlayers;
		}
		virtual int GetWinner() override
		{
			return m_currentPlayer;
		}

	private:
		int m_numOfTurns;
		int m_currentTurn{0};
		int m_currentPlayer{ 0 };
	};
}

void TemplateExample() {
	using namespace TemplateNamespace;

	Chess chess{10};
	chess.run();
}