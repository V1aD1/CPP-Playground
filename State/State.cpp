#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

namespace StateNamespace {
	enum class State {
		offHook, 
		connecting, 
		connected,
		onHook
	};

	inline ostream& operator<<(ostream& os, const State& s) {
		switch (s) {
		case State::connected:
			os << "connected";
			break;
		case State::connecting:
			os << "connecting";
			break;
		case State::offHook:
			os << "off the hook";
			break;
		case State::onHook:
			os << "on hook";
			break;
		default: break;
		}
		return os;
	}

	enum class Trigger {
		callDialed,
		hangUp,
		callConnected,
		leftMessage, 
	};

	inline ostream& operator<<(ostream& os, const Trigger& t) {
		switch (t)
		{
		case Trigger::callDialed:
			os << "call dialed";
			break;
		case Trigger::callConnected:
			os << "call connected";
			break;
		case Trigger::hangUp:
			os << "hang up";
			break;
		case Trigger::leftMessage:
			os << "left a message";
			break;
		default: break;
		}

		return os;
	}
}

void StateExample() {
	using namespace StateNamespace;
	map<State, vector<pair<Trigger, State>>> rules;
	
	rules[State::offHook] = {
		{Trigger::callDialed, State::connecting},
		{Trigger::hangUp, State::onHook}
	};

	rules[State::connecting] = {
		{Trigger::callConnected, State::connected},
		{Trigger::hangUp, State::onHook}
	};

	rules[State::connected] = {
		{Trigger::leftMessage, State::onHook},
		{Trigger::hangUp, State::onHook}
	};

	State currentState{ State::offHook }, exitState{ State::onHook };

	while (true) {
		cout << "The phone is currently " << currentState << endl;
	select_trigger:
		cout << "Select a trigger: " << endl;

		int i = 0;
		for (auto item : rules[currentState]) {
			cout << i++ << ". " << item.first << endl;
		}

		int input;
		cin >> input;
		if (input < 0 || (input + 1) > rules[currentState].size()) {
			cout << "Incorrect option, please try again" << endl;
			goto select_trigger;
		}

		currentState = rules[currentState][input].second;
		if (currentState == exitState) break;
	}

	cout << "We are done using the telephone" << endl;
	cin.get();
}