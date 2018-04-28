#include "../stdafx.h"
#include "tree_gen.h"

using std::vector;
using std::string;
using std::cout;

namespace BinaryTree {
	/**
	* Default constructor
	*/
	BinaryTree::BinaryTree() {
		root_ = nullptr;
	}

	/**
	* Make the tree from the vector of part-of-speech tags
	*
	*@param tags the vector that contains the tags
	*/
	BinaryTree::BinaryTree(vector<string> tags) {
		if (tags.size() == 0) {
			root_ = nullptr;
			return;
		}

		//Check for D's before N's

		//Vector to store the phrase subtrees
		vector<Node*> phrases;

		//Storing the phrase subtrees returned by create_phrase()
		for (auto tag : tags) {
			phrases.push_back(create_phrase(tag));
		}

		//Initialize the root of the tree
		root_ = phrases.front();

		build_tree(phrases);
	}

	/**
	* Destructor
	*/
	BinaryTree::~BinaryTree()
	{
		clear(this->root_);
	}

	/**
	* Combine the subtrees into a single binary tree
	*/
	void BinaryTree::build_tree(vector<Node*> phrases) {
		int i = 0, j = 0;

		for (; i < phrases.size(); i++) {
			j = i;

			if (phrases.at(i)->label == "DP") { //DP phrases
				while (phrases.at(j)->label != "NP") { //Iterate to the next NP
					j++;
				}

				phrases.at(i)->left->right = phrases.at(j); //Take the next NP as a complement - sister to head
			}
			else if (phrases.at(i)->label == "NP") { //NP phrases
				while (phrases.at(j)->label != "DP") { //Iterate to the previous DP
					j--;
				}
				j++; //Go to the phrase after the DP

				//Go until the next VP or till the end of the sentence
				while (phrases.at(j)->label != "VP" || j < phrases.size()) { 
					//If these phrases are PPs or AdjPs and this NP has at least one adjunct
					if (phrases.at(j)->label == "PP" || phrases.at(j)->label == "AdjP") {
						//Create a new bar level
						Node *new_bar;

						//Take the j phrase and the previous bar level as a children of the new bar level
						if (j < i) {
							new_bar = new Node("N'", phrases.at(j), phrases.at(i)->left);
						}
						else {
							new_bar = new Node("N'", phrases.at(i)->left, phrases.at(j));
						}

						//Take the new bar level as a child of the phrase level
						phrases.at(i)->left = new_bar;
					}

					j++;
				}
			}
			else if (phrases.at(i)->label == "VP") { //VP phrases
				if (phrases.at(i - 1)->label == "AdvP") { //Check for an adverb preceding the verb
					Node *new_bar = new Node("V'", phrases.at(j), phrases.at(i)->left);
					phrases.at(i)->left = new_bar;
				}
				while (++j < phrases.size()) { //Add all phrases following V 
					Node *new_bar = new Node("V'", phrases.at(i)->left, phrases.at(j));
					phrases.at(i)->left = new_bar;
				}
			}
			else if (phrases.at(i)->label == "AdjP") {
				while (j > 0 && phrases.at(j)->label != "DP") {
					j--;
					if (phrases.at(j)->label == "AdvP" && phrases.at(i)->left->right) {
						Node *new_bar = new Node("Adj'", phrases.at(i)->left, phrases.at(j));
						phrases.at(i)->left = new_bar;
					}
					else if (phrases.at(j)->label == "AdvP") {
						phrases.at(i)->left->right = phrases.at(i)->left->left;
						phrases.at(i)->left->left = phrases.at(j);
					}
				}
			}
		}
	}

	/**
	* Default constructor
	*/
	Node* BinaryTree::create_phrase(string tag) {
		Node *head = new Node(tag);
		Node *bar = new Node(tag + "'", head);
		Node *phrase = new Node(tag + "P", bar);

		return phrase;
	}

	/**
	* Clear the tree
	*/
	void BinaryTree::clear(Node *to_clear) {
		if (!to_clear) {
			return;
		}
		if (to_clear->left) {
			clear(to_clear->left);
		}
		if (to_clear->right) {
			clear(to_clear->right);
		}

		delete to_clear;
		to_clear = nullptr;
	}

	int BinaryTree::count() {
		return count(this->root_);
	}

	int BinaryTree::count(Node *current) {
		if (!current) {
			return 0;
		}
		if (current->left) {
			count(current->left);
		}
		if (current->right) {
			count(current->right);
		}
		return 1;
	}
}