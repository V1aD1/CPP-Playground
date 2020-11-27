#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace CommandNamespace {
	struct BankAccount {
		int m_balance = 0;
		int m_overdraftLimit = -500;

		void deposit(int amount) {
			m_balance += amount;
			cout << "Deposited " << amount << "$ into account, balance is now: " << m_balance << "$\n";
		}

		void withdraw(int amount) {
			if (m_balance - amount > m_overdraftLimit) {
				m_balance -= amount;
				cout << "Withdrew " << amount << "$ from account, balance is now: " << m_balance << "$\n";
			}
		}

		friend ostream& operator<<(ostream& os, const BankAccount& account) {
			os << "Balance: " << account.m_balance;
			return os;
		}
	};

	struct Command {
		virtual void call() = 0;
	};

	struct BankAccountCommand : Command {
		BankAccount& m_account;
		enum Action {deposit, withdraw} m_action;
		int m_amount;

		BankAccountCommand(BankAccount& account, Action action, int amount):
			m_account(account), m_action(action), m_amount(amount){}
	
		void call() override {
			switch (m_action) {
			case deposit:
				m_account.deposit(m_amount);
				break;
			case withdraw:
				m_account.withdraw(m_amount);
				break;
			}
		}
	};
}

void CommandExample() {
	using namespace CommandNamespace;

	BankAccount acc{};

	vector<BankAccountCommand> commands{
		BankAccountCommand{ acc, BankAccountCommand::Action::deposit, 100 },
		BankAccountCommand{ acc, BankAccountCommand::Action::withdraw, 200 }
	};
	for (auto& cmd : commands)
		cmd.call();

	cout << acc << endl;
}