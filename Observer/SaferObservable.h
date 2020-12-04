#pragma once
#include <vector>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

template <typename T>
struct Observer;

/// <summary>
/// Observer class is not thread safe, because there's one function that iterates
/// over m_observers (onFieldChanged), and other functions that modify it (Subscribe/Unsubscribe)
/// 
/// SaferObserver is threadsafe because every function must require a lock before proceeding
/// </summary>
template <typename T>
class SaferObservable
{
	vector<Observer<T>*> m_observers;
	mutex mtx;

protected:
	void OnFieldChanged(T& source, const string& fieldName) {
		scoped_lock<mutex> lock{ mtx };

		for (auto&& observer : m_observers) {
			observer->FieldChanged(source, fieldName);
		}
	}

public:
	void Subscribe(Observer<T>& subscriber) {
		scoped_lock<mutex> lock{ mtx };
		m_observers.push_back(&subscriber);
	}

	void Unsubscribe(Observer<T>& subscriber) {
		scoped_lock<mutex> lock{ mtx };

		// we are removing the subscriber from m_observers using the erase remove idiom,
		// which is a more efficient way of removing from a standard library container.
		// In the case of a vector, all elements need to be contiguous, so when you remove
		// an element, all the following elements must be shifted backwards to avoid any gaps.
		// The erase function however shuffles all the elements that are going to get erased
		// to the end of the collection, thereby making the erase operation much faster
		// Read more here: https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		m_observers.erase(
			remove(m_observers.begin(), m_observers.end(), &subscriber),
			m_observers.end()
		);
	}
};

