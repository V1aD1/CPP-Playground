#include <algorithm> 
#include <string>
#include <iostream>

using namespace std;

namespace Facade {
	struct Car {
		float m_speed = 0.0f;
		float m_dirInDegs = 0.0f;
		float m_gas = 0.0f;
		bool m_inDrive = false;
		const static float m_startGasCost;

		void Start() {
			if (m_inDrive == true)
				return;

			if (m_gas < m_startGasCost)
				return;

			m_gas -= m_startGasCost;
			m_inDrive = true;
			cout << "Started car" << endl;
		}

		void Accelerate(float acc, float dt) {
			float costOfAcc = std::min(acc * dt * 1.2f, m_gas);
			float accToApply = Car::GetAccFromGasCost(costOfAcc, dt);

			m_speed += accToApply * dt;
		}

		void Turn(float degrees) {
			m_dirInDegs += degrees;
		}

		void TurnOnHeating() {
			cout << "Turned on heating" << endl;
		}

		void AdjustSeats() {
			cout << "Adjusted seats" << endl;
		}

		void FillUpTank(float amount) {
			m_gas += amount;
			cout << "Filled tank with : " << amount << " L of fuel" << endl;
		}

		static float GetAccFromGasCost(float gasUsed, float dt) {
			return gasUsed / dt / 1.2f;
		}
	};

	const float Car::m_startGasCost = 3.0f;

	struct CarFacade {
		Car& m_car;

		CarFacade(Car& car) : m_car(car) {}

		// starting a Car is a complicated process, so let's simplify it by adding
		// all the steps into this one method
		void Go() {
			if (m_car.m_inDrive)
				return;

			if (m_car.m_gas < m_car.m_startGasCost)
				m_car.FillUpTank(Car::m_startGasCost);

			m_car.Start();
			m_car.AdjustSeats();
			m_car.TurnOnHeating();
		}
	};
}

void FacadeExample() {
	using namespace Facade;

	// instead of trying to use the Vehicle object directly,
	// use the simplified CarFacade instead
	Car c{};
	CarFacade vf{ c };

	vf.Go();
}
