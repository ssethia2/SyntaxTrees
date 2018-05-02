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
	* Vector value constructor
	* Make the tree from the vector of part-of-speech tags
	*
	*@param tags the vector that contains the tags
	*/
	BinaryTree::BinaryTree(vector<string> tags) {
		root_ = nullptr;
		CreateTree(tags);
	}

	/**
	* Destructor
	*/
	BinaryTree::~BinaryTree()
	{
		clear(this->root_);
	}

	//--------------------------------------------------------------------------------------------------------------------

	/**
	* Create phrases for all tags
	*
	* @param tag the tag to create the phrase for
	* @return the pointer to the node that is the phrase for the tag
	*/
	Node* BinaryTree::CreatePhrase(string tag) {
		Node *head = new Node(tag);
		Node *bar = new Node(tag + "'", head);
		Node *phrase = new Node(tag + "P", bar);

		return phrase;
	}

	/**
	* Create tree for the tags
	*
	* @param tag the tags to create the tree for
	*/
	void BinaryTree::CreateTree(vector<string> tags) {
		if (tags.size() == 0) {
			root_ = nullptr;
			return;
		}

		//Checking if sentence has a determiner, if not, add one for null D
		if (tags.front() != "D") {
			tags.push_back("D");
		}

		//Vector to store the phrase subtrees
		vector<Node*> phrases;

		//Storing the phrase subtrees returned by CreatePhrase()
		for (auto tag : tags) {
			phrases.push_back(CreatePhrase(tag));
		}

		BuildTree(phrases);
	}

	/**
	* Combine the subtrees into a single binary tree
	*/
	void BinaryTree::BuildTree(vector<Node*> &phrases) {
		for (int prime_iter = 0; prime_iter < phrases.size(); prime_iter++) {
			if (phrases.at(prime_iter)->label == "DP") { //DP phrases
				DPhrase(phrases, prime_iter, prime_iter);
			}
			else if (phrases.at(prime_iter)->label == "NP") { //NP phrases
				NPhrase(phrases, prime_iter, prime_iter);
			}
			else if (phrases.at(prime_iter)->label == "VP") { //VP phrases
				VPhrase(phrases, prime_iter, prime_iter);
			}
			else if (phrases.at(prime_iter)->label == "AdjP") {
				AdjPhrase(phrases, prime_iter, prime_iter);
			}
			else if (phrases.at(prime_iter)->label == "PP") {
				PPhrase(phrases, prime_iter, prime_iter);
			}
		}

		CPhrase(phrases);
	}

	//--------------------------------------------------------------------------------------------------------------------

	/**
	* Create subtree for DPs
	*
	* @param phrases vector that contains the phrases that haven't been included in a subtree yet
	*/
	void BinaryTree::DPhrase(vector<Node*>& phrases, int prime_iter, int sec_iter) {
		while (phrases.at(sec_iter)->label != "NP") { //Iterate to the next NP
			sec_iter++;
		}

		phrases.at(prime_iter)->left->right = phrases.at(sec_iter); //Take the next NP as a complement - sister to head
	}

	/**
	* Create subtree for NPs
	*
	* @param phrases vector that contains the phrases that haven't been included in a subtree yet
	*/
	void BinaryTree::NPhrase(vector<Node*>& phrases, int prime_iter, int sec_iter) {
		//Check for PP immediately following NP starting with 'of' to add to complement
		/*if (phrases.at(prime_iter + 1)->label == "PP") {
			if (syntax.at(prime_iter + 1) == 'of'){
				phrases.at(prime_iter)->left->right = phrases.at(sec_iter); //Take the 'of' PP as a complement - sister to head
			}
			
		}*/

		bool is_after_vp = true;
		while (sec_iter < phrases.size()) {
			if (phrases.at(sec_iter++)->label == "VP") {
				is_after_vp = false;
				break;
			}
		}
		sec_iter = prime_iter;

		while (phrases.at(sec_iter)->label != "DP") { //Iterate to the previous DP
			sec_iter--;
		}
		sec_iter++; //Go to the phrase after the DP

		//Go until the next VP or till the end of the sentence
		while (sec_iter < phrases.size() && phrases.at(sec_iter)->label != "VP") {
			//If these phrases are PPs or AdjPs and this NP has at least one adjunct
			if ((sec_iter > prime_iter && !is_after_vp && phrases.at(sec_iter)->label == "PP") || phrases.at(sec_iter)->label == "AdjP") {
				//Create a new bar level
				Node *new_bar;

				//Take the j phrase and the previous bar level as a children of the new bar level
				if (sec_iter < prime_iter) {
					new_bar = new Node("N'", phrases.at(sec_iter), phrases.at(prime_iter)->left);
				}
				else {
					new_bar = new Node("N'", phrases.at(prime_iter)->left, phrases.at(sec_iter));
				}

				//Take the new bar level as a child of the phrase level
				phrases.at(prime_iter)->left = new_bar;
			}

			sec_iter++;
		}
	}

	/**
	* Create subtree for VPs
	*
	* @param phrases vector that contains the phrases that haven't been included in a subtree yet
	*/
	void BinaryTree::VPhrase(vector<Node*>& phrases, int prime_iter, int sec_iter) {
		/*bool is_dp_after_vp = false;
		while (sec_iter < phrases.size()) {
			if (phrases.at(sec_iter++)->label == "DP") {
				is_dp_after_vp = true;
				break;
			}
		}
		sec_iter = prime_iter;*/

		bool is_dp_added = false;
		
		while (++sec_iter < phrases.size()) { //Add all phrases following V 
			if ((!is_dp_added && phrases.at(sec_iter)->label == "DP") || phrases.at(sec_iter)->label == "AdvP" || phrases.at(sec_iter)->label == "PP") {
				//Check for direct objects if possible

				Node *new_bar = new Node("V'", phrases.at(prime_iter)->left, phrases.at(sec_iter));
				phrases.at(prime_iter)->left = new_bar;

				if (phrases.at(sec_iter)->label == "DP") {
					is_dp_added = true;
				}
			}
		}

		//Check for an adverb preceding the verb and add it as the top most adjunct
		if (phrases.at(prime_iter - 1)->label == "AdvP") { 
			Node *new_bar = new Node("V'", phrases.at(sec_iter), phrases.at(prime_iter)->left);
			phrases.at(prime_iter)->left = new_bar;
		}
	}

	/**
	* Create subtree for PPs
	*
	* @param phrases vector that contains the phrases that haven't been included in a subtree yet
	*/
	void BinaryTree::PPhrase(vector<Node*>& phrases, int prime_iter, int sec_iter) {
		while (sec_iter < phrases.size() && (phrases.at(++sec_iter)->label != "PP" || phrases.at(++sec_iter)->label != "VP")) {
			if (phrases.at(sec_iter)->label == "DP" || phrases.at(sec_iter)->label == "NP") {
				Node *new_bar = new Node("P'", phrases.at(prime_iter)->left, phrases.at(sec_iter));
				phrases.at(prime_iter)->left = new_bar;
			}
		}
	}

	/**
	* Create subtree for AdjPs
	*
	* @param phrases vector that contains the phrases that haven't been included in a subtree yet
	*/
	void BinaryTree::AdjPhrase(vector<Node*>& phrases, int prime_iter, int sec_iter) {
		while (sec_iter > 0 && phrases.at(sec_iter)->label != "DP") {
			sec_iter--;
			if (phrases.at(sec_iter)->label == "AdvP" && phrases.at(prime_iter)->left->right) {
				Node *new_bar = new Node("Adj'", phrases.at(prime_iter)->left, phrases.at(sec_iter));
				phrases.at(prime_iter)->left = new_bar;
			}
			else if (phrases.at(sec_iter)->label == "AdvP") {
				phrases.at(prime_iter)->left->right = phrases.at(prime_iter)->left->left;
				phrases.at(prime_iter)->left->left = phrases.at(sec_iter);
			}
		}
	}

	/**
	* Create tree with root as the sentence S
	*
	* @param phrases vector that contains the subject DP and VP
	*/
	void BinaryTree::CPhrase(vector<Node*>& phrases) {
		for (auto phrase : phrases) {
			if (phrase->label == "VP") {
				root_ = new Node("S", phrases.at(0), phrase);
				break;
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------------------

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

	/**
	* Count the number of nodes in the tree
	*/
	int BinaryTree::count() {
		return count(this->root_);
	}

	/**
	* Count the number of nodes in the subtree with root at current
	*
	* @param current pointer to the root of the subtree whose nodes have to be counted
	*/
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