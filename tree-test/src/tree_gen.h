#ifndef tree_gen_h
#define tree_gen_h

#include <utility>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace BinaryTree {
	struct Node {
		string label;
		Node *left;
		Node *right;

		Node(string lab = NULL, Node *new_left = nullptr, Node *new_right = nullptr, Node *new_parent = nullptr) {
			label = lab;
			left = new_left;
			right = new_right;
		}
	};

	class BinaryTree {
	public:
		Node * root_;

		BinaryTree();
		BinaryTree(vector<string> tags);
		~BinaryTree();

		void build_tree(vector<Node*> phrases);
		struct Node* create_phrase(string tag);
		void clear(Node * to_clear);
		int count();
		int count(Node *current);
	};
}

#endif //tree_gen_h