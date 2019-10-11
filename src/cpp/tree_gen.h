#ifndef tree_gen_h
#define tree_gen_h

#include <utility>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace BinaryTree {
	/**
	* A structure that models a node of a binary tree.
	*/
	struct Node {
		string label;	//Value of the node
		Node *left;		//Pointer to left child (root of left subtree)
		Node *right;	//Pointer to right child (root of right subtree)

		/**
		* Parametrized constructor for Node with default values for unspecified parameters.
		*
		* @param lab label of the node. NULL (0) by default.
		* @param new_left pointer to left child. 'nullptr' by default.
		* @param new_right pointer to right child. 'nullptr' by default.
		*/
		Node(string lab = NULL, Node *new_left = nullptr, Node *new_right = nullptr) {
			label = lab;
			left = new_left;
			right = new_right;
		}
	};

	/**
	* Class that implements a binary tree.
	*/
	class BinaryTree {

	public:
		Node * root_; //Root of the tree

	/* Root is public for testing.
	   It can be made private once an iterator class for the tree is created, with minor changes to unit tests.
	 */

	//--------------------------------------------------------------------------------------------------------------------

		BinaryTree();						//Default constructor
		BinaryTree(vector<string> tags);	//Vector-value constructor
		~BinaryTree();						//Destructor

	//--------------------------------------------------------------------------------------------------------------------

		Node* CreatePhrase(string tag);			//Create phrase for tag

		void CreateTree(vector<string> tags);	//Create tree
		void BuildTree(vector<Node*> &phrases);	//Combine subtrees


	//--------------------------------------------------------------------------------------------------------------------

		void DPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter);		//Build DP subtree
		void NPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter);		//Build NP subtree
		void VPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter);		//Build VP subtree
		void PPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter);		//Build PP subtree
		void AdjPhrase(vector<Node*> &phrases, int prime_iter, int sec_iter);	//Build AdjP subtree
		void CPhrase(vector<Node*> &phrases);									//Build CP subtree

	//--------------------------------------------------------------------------------------------------------------------

		void clear();					//Clear the tree
		void clear(Node * to_clear);	//Clear the subtree with specified root
		int count();					//Count nodes in tree
		int count(Node *current);		//Count nodes in subtree with root current
	};
}

#endif //tree_gen_h