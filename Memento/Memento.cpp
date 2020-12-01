#include <ostream>
#include <iostream>
#include <string>

using namespace std;

namespace MementoNamespace {
	class Memento {

		// it's important for these members to be private so that they cannot be tampered with,
		// except by BankAccount
		int m_balance;
		Memento(int balance) : m_balance(balance) {}

		friend class BankAccount;
	};

	struct BankAccount {
		int m_balance{ 0 };

		Memento deposit(int amount) {
			m_balance += amount;

			// Memento constructor is used here implicitly
			return { m_balance };
		}

		Memento withdraw(int amount) {
			if (m_balance - amount >= 0)
				m_balance -= amount;

			// Memento constructor is used here implicitly
			return { m_balance };
		}

		void Restore(Memento memento) {
			m_balance = memento.m_balance;
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
	Memento mem1 = account.deposit(100);
	cout << account << endl;

	Memento mem2 = account.withdraw(50);
	cout << account << endl;

	account.Restore(mem1);
	cout << account << endl;
}