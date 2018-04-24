#include "tree_gen.h"

using std::vector;
using std::string;

BinaryTree::BinaryTree() {
	root_ = nullptr; 
}

void BinaryTree::create_tree(vector<string> tags) {
	vector<struct Node*> phrases;

	for (auto tag : tags) {
		phrases.push_back(create_phrase(tag));
	}
}

struct Node* create_phrase(string tag) {
	Node *head = new Node(tag);
	Node *bar = new Node(tag+"'", head);
	Node *phrase = new Node(tag+"P", bar);
}