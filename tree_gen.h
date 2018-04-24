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
			parent = new_parent;
		}
	};

	class BinaryTree {
	private:
		Node * root_;

	public:
		BinaryTree();
		void create_tree(vector<string> tags);
		void build_tree(vector<struct Node*>& phrases);
		struct Node* create_phrase(string tag);
	};
}

#endif //tree_gen_h