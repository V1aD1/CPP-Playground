#include <string>
#include <iostream>

using namespace std;

namespace BinaryTreeIterator {
	//     A
	//    / \
	//   B   C
	template <typename T> struct BinaryTree;

	template <typename T> struct Node {
		T value = T();
		Node<T>* left{ nullptr }, * right{ nullptr }, * parent{ nullptr };
		BinaryTree<T>* tree{ nullptr };

		Node(T value) : value(value) {}

		Node(T value, Node<T>* left, Node<T>* right) : value(value), right(right), left(left) {
			if (this->left) { 
				this->left->tree = tree; 
				this->left->parent = this;
			}
			if (this->right) { 
				this->right->tree = tree; 
				this->right->parent = this;
			}
		}

		void setTree(BinaryTree<T>* t) {
			tree = t;
			if (left) left->setTree(t);
			if (right) right->setTree(t);
		}

		~Node() {
			if (left) 
				delete left;
			if (right) 
				delete right;
		}

		friend ostream& operator<<(ostream& os, const Node<T>& node) {
			os << node.value;
			return os;
		}
	};

	template <typename T> struct BinaryTree {
		Node<T>* root{ nullptr };
		BinaryTree(Node<T>* root) : root(root) {
			root->setTree(this);
		}

		~BinaryTree() {
			if (root) delete root;
		}

		template <typename U> struct InOrderIterator {
			Node<U>* current;
			InOrderIterator(Node<U>* current) : current(current) {}

			bool operator!=(const InOrderIterator<U>& other) {
				return current != other.current;
			}

			InOrderIterator<U>& operator++() {
				if (current->right) {
					current = current->right;
					while (current->left) {
						current = current->left;
					}
				}
				else {
					Node<T>* p = current->parent;
					while (p && current == p->right) {
						current = p;
						p = p->parent;
					}
					current = p;
				}
				return *this;
			}

			Node<U>& operator*() { return *current; }
		};

		InOrderIterator<T> begin() {
			Node<T>* n = root;

			if (n) {
				while (n->left) {
					n = n->left;
				}
				return InOrderIterator<T>{n};
			}
		}

		InOrderIterator<T> end() {
			return InOrderIterator<T>{nullptr};
		}
	};
}

void BinaryTreeIteratorExample() {
	using namespace BinaryTreeIterator;

	//       parent
	//        /  \
	//    child1 child2
	//      /
	//  grandchild

	Node<string>* grandchild = new Node<string>{ "grandchild" };
	Node<string>* child1 = new Node<string>{ "child1", grandchild, nullptr };
	Node<string>* child2 = new Node<string>{ "child2"};
	Node<string>* parent = new Node<string>{ "parent", child1, child2};

	BinaryTree<string> family{ parent };

	for (auto it = family.begin(); it != family.end(); ++it) {
		cout << *it << endl;
	}
}
