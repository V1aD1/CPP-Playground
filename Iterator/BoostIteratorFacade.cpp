#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>

using namespace std;

namespace BoostIteratorFacade {
	/// <summary>
	/// Node used in a SINGLY linked list
	/// </summary>
	struct Node {
		string m_value;
		Node* m_next{ nullptr };

		Node(const string& value) : m_value(value) {}
		Node(const string& value, Node* parent) : m_value(value) {
			parent->m_next = this;
		}
	};

	struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag> {
		Node* m_current{ nullptr };
		ListIterator() {}
		ListIterator(Node* current) : m_current(current) {}
	private:
		// allows iterator_core_access to access private members of ListIterator
		friend class boost::iterator_core_access;

		// even though these aren't overridden methods, the iterator facade will use
		// them for iteration if they exist
		void increment() { m_current = m_current->m_next; }

		bool equal(const ListIterator& other) const {
			return m_current == other.m_current;
		}

		Node& dereference() const {
			return *m_current;
		}
	};
}

void BoostIteratorFacadeExample() {
	using namespace BoostIteratorFacade;

	Node alpha{ "alpha" };
	Node beta{ "beta", &alpha };
	Node gamma{ "gamma", &beta };

	// added in C++11, params are: beginning, end, then function to apply to each element
	for_each(ListIterator{ &alpha }, ListIterator{}, [](const Node& node)
		{
			cout << node.m_value << endl;
		});
}