#include <ostream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace MementoNamespace {
	class Memento {

		// it's important for these members to be private so that they cannot be tampered with,
		// except by BankAccount
		int m_balance;
		Memento(int balance) : m_balance(balance) {}

		// even though BankAccount is a friend, make_shared ISN'T a friend, so we can't use it
		friend struct BankAccount;
	};

	struct BankAccount {
		int m_balance{ 0 };
		int current{ 0 };
		vector<shared_ptr<Memento>> changes;

		shared_ptr<Memento> deposit(int amount) {
			// first remove all elements after changes[current], because they
			// need to get discarded since deposit should be at the top of the stack
			changes.erase(changes.begin() + current, changes.end());

			m_balance += amount;

			// make, add, and return memento
			// can't use make_shared here because make_shared isn't a friend of Memento,
			// so we do it using the shared_ptr constructor directly
			auto memento = shared_ptr<Memento>(new Memento{ m_balance });
			changes.push_back(memento);
			current++;
			return memento;
		}

		shared_ptr<Memento> withdraw(int amount) {
			if (m_balance - amount < 0) { 
				// can't use make_shared here because make_shared isn't a friend of Memento,
				// so we do it using the shared_ptr constructor directly
				return shared_ptr<Memento>(new Memento{ m_balance }); 
			}

			// first remove all elements after changes[current], because they
			// need to get discarded since withdraw should be at the top of the stack
			changes.erase(changes.begin() + current, changes.end());

			m_balance -= amount;

			// make, add, and return memento
			// can't use make_shared here because make_shared isn't a friend of Memento,
			// so we do it using the shared_ptr constructor directly
			auto memento = shared_ptr<Memento>(new Memento{ m_balance });
			changes.push_back(memento);
			current++;
			return memento;
		}

		void Restore(shared_ptr<Memento>& memento) {
			m_balance = memento->m_balance;

			// add memento to end of stack
			changes.push_back(memento);
			current = changes.size() - 1;
		}

		void Undo() {

			// cannot undo if at the beginning of the stack
			if (current == 0) { return; }

			current--;
			m_balance = changes[current]->m_balance;
		}

		void Redo() {
			// cannot redo if at end of stack
			if (current == changes.size() - 1) { return; }

			current++;
			m_balance = changes[current]->m_balance;
		}

		friend ostream& operator<<(ostream& os, const BankAccount& account) {
			os << "Balance: " << account.m_balance;
			return os;
		}
	};
}

void MementoExample() {
	using namespace MementoNamespace;

	BankAccount account{};
	auto mem1 = account.deposit(100);
	cout << "Account after deposit : " << account << endl;

	auto mem2 = account.withdraw(50);
	cout << "Account after withdrawal: " << account << endl;

	account.Restore(mem1);
	cout << "Account after restore: " << account << endl;

	account.Undo();
	cout << "Balance after undo: " << account << endl;

	account.Redo();
	cout << "Balance after redo: " << account << endl;
}