//#include "tree_gen.h"
//
//using std::vector;
//using std::string;
//using std::cout;
//
//namespace BinaryTree {
//	/**
//	* Default constructor
//	*/
//	BinaryTree::BinaryTree() {
//		root_ = nullptr;
//	}
//
//	/**
//	* Make the tree from the vector of part-of-speech tags
//	*
//	*@param tags the vector that contains the tags
//	*/
//	BinaryTree::BinaryTree(vector<string> tags) {
//		if (tags.size() == 0) {
//			return;
//		}
//
//		//Check for D's before N's
//
//		//Vector to store the phrase subtrees
//		vector<struct Node*> phrases;
//
//		//Storing the phrase subtrees returned by create_phrase()
//		for (auto tag : tags) {
//			phrases.push_back(create_phrase(tag));
//		}
//
//		//Initialize the root of the tree
//		root_ = phrases.front();
//
//		build_tree(phrases);
//	}
//
//	/**
//	* Destructor
//	*/
//	BinaryTree::~BinaryTree()
//	{
//		clear(this->root_);
//	}
//
//	/**
//	* Combine the subtrees into a single binary tree
//	*/
//	void BinaryTree::build_tree(vector<struct Node*> phrases) {
//		int i = 0, j = 0;
//
//		for (i = 0; i < phrases.size(); i++) {
//			j = i;
//
//			if (phrases.at(i)->label == "DP") {
//				while (phrases.at(j)->label != "NP") {
//					j++;
//				}
//
//				phrases.at(i)->right = phrases.at(j);
//			}
//			else if (phrases.at(i)->label == "NP") {
//				while (phrases.at(j)->label != "DP") {
//					j--;
//				}
//				j++;
//
//				while (phrases.at(j)->label != "VP" || j < phrases.size()) {
//					if (phrases.at(j)->label != "PP" || phrases.at(j)->label != "AdjP") {
//						Node *new_bar;
//
//						if (j < i) {
//							new_bar = new Node("N'", phrases.at(j), phrases.at(i)->left);
//						}
//						else {
//							new_bar = new Node("N'", phrases.at(i)->left, phrases.at(j));
//						}
//
//						phrases.at(i)->left = new_bar;
//					}
//
//					j++;
//				}
//			}
//			else if (phrases.at(i)->label == "VP") {
//				while (j < phrases.size()) {
//					Node *new_bar = new Node("V'", phrases.at(i)->left, phrases.at(j));
//					phrases.at(i)->left = new_bar;
//
//					j++;
//				}
//			}
//			else if (phrases.at(i)->label == "AdjP") {
//				while (j > 0 && phrases.at(j)->label != "DP") {
//					j--;
//					if (phrases.at(j)->label == "AdvP") {
//						Node *new_bar = new Node("Adj'", phrases.at(i)->left, phrases.at(j));
//						phrases.at(i)->left = new_bar;
//					}
//				}
//			}
//		}
//	}
//
//	/**
//	* Default constructor
//	*/
//	Node* create_phrase(string tag) {
//		Node *head = new Node(tag);
//		Node *bar = new Node(tag + "'", head);
//		Node *phrase = new Node(tag + "P", bar);
//
//		return phrase;
//	}
//
//	/**
//	* Clear the tree
//	*/
//	void clear(Node *to_clear) {
//		if (to_clear->left) {
//			clear(to_clear->left);
//		}
//		if (to_clear->right) {
//			clear(to_clear->right);
//		}
//
//		delete to_clear;
//		to_clear = nullptr;
//	}
//
//	int BinaryTree::count() {
//		return count(this->root_);
//	}
//
//	int BinaryTree::count(Node *current) {
//		if (current->left) {
//			count(current->left);
//		}
//		if (current->right) {
//			count(current->right);
//		}
//		return 1;
//	}
//}