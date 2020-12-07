#pragma once
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// This is the old implementation of the state pattern which you'll see in some books.
/// It is outdated, and weird, and shouldn't be used in production. Check out the 
/// other implementations of the state pattern to see how to PROPERLY do it.
/// </summary>
namespace OutdatedState {
	class LightSwitch;
	
	struct State
	{
		virtual void On(LightSwitch* lightSwitch) {
			cout << "Light is already on \n";
		}

		virtual void Off(LightSwitch* lightSwitch) {
			cout << "Light is already off \n";
		}
	};

	struct OnState : State {
		OnState() {
			cout << "Light is turned on \n";
		}

		// basically the state implements the OPPOSITE method to make the state change
		void Off(LightSwitch* lightSwitch) override;
	};

	struct OffState : State {
		OffState() {
			cout << "Light is turned off \n";
		}

		// basically the state implements the OPPOSITE method to make the state change
		void On(LightSwitch* lightSwitch) override;
	};

	class LightSwitch {
		State* m_state;
	public:
		LightSwitch() {
			m_state = new OffState();
		}

		void SetState(State* state) {
			this->m_state = state;
		}

		void On() { m_state->On(this); }
		void Off() { m_state->Off(this); }
	};

	void OnState::Off(LightSwitch* lightSwitch) {
		cout << "Switching light off...\n";
		lightSwitch->SetState(new OffState());
		delete this; // big red flag
	}

	void OffState::On(LightSwitch* lightSwitch) {
		cout << "Switching light on...\n";
		lightSwitch->SetState(new OnState());
		delete this; // big red flag
	}
}

void OutdatedStateExample() {
	using namespace OutdatedState;

	// apparently we can also initialize without brackets at all?
	// if you don't have any brackets then it implicityle calls the default constructor
	// this us equivalent to "LightSwitch ls{};"
	LightSwitch ls;
	ls.On();
	ls.Off();
	ls.Off();
}