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
		Node * root_; //Root of the tree

		//--------------------------------------------------------------------------------------------------------------------

		BinaryTree(); //Default constructor
		BinaryTree(vector<string> tags); //Vector-value constructor
		~BinaryTree(); //Destructor

		//--------------------------------------------------------------------------------------------------------------------

		Node* CreatePhrase(string tag); //Create phrase for tag

		void CreateTree(vector<string> tags); //Create tree
		void BuildTree(vector<Node*> &phrases); //Combine subtrees


		//--------------------------------------------------------------------------------------------------------------------

		void DPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter); //Build DP subtree
		void NPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter); //Build NP subtree
		void VPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter); //Build VP subtree
		void PPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter); //Build PP subtree 
		void AdjPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter); //Build AdjP subtree
		void CPhrase(vector<Node*> &phrases); //Build CP subtree

		//--------------------------------------------------------------------------------------------------------------------

		void clear(Node * to_clear); //Clear the tree
		int count(); //Count nodes in tree
		int count(Node *current); //Count nodes in subtree with root current
	};
}

#endif //tree_gen_h