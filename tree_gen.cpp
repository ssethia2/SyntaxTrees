#include "tree_gen.h"

using std::vector;
using std::string;
using std::cout;

namespace BinaryTree {
	BinaryTree::BinaryTree() {
		root_ = nullptr;
	}

	void BinaryTree::create_tree(vector<string> tags) {
		if (tags.size() == 0) {
			return;
		}

		//Check for D's before N's


		vector<struct Node*> phrases;

		for (auto tag : tags) {
			phrases.push_back(create_phrase(tag));
		}

		for (auto x : phrases) {
			cout << x->label;
		}

		build_tree(phrases);
	}

	void BinaryTree::build_tree(vector<struct Node*>& phrases) {
		root_ = phrases.front();

		int i = 1, j = 0;

		for (i = 1; i < phrases.size(); i++) {
			j = i;

			if (phrases.at(i)->label == "DP") {
				while (phrases.at(j)->label != "NP") {
					j++;
				}

				phrases.at(i)->right = phrases.at(j);
			}
			else if (phrases.at(i)->label == "NP") {
				while (phrases.at(j)->label != "DP") {
					j--;
				}
				j++;

				while (phrases.at(j)->label != "VP" || j < phrases.size()) {
					if (phrases.at(j)->label != "PP" || phrases.at(j)->label != "AdjP") {
						Node *new_bar;

						if (j < i) {
							new_bar = new Node("N'", phrases.at(j), phrases.at(i)->left);
						}
						else {
							new_bar = new Node("N'", phrases.at(i)->left, phrases.at(j));
						}

						phrases.at(i)->left = new_bar;
					}

					j++;
				}
			}
			else if (phrases.at(i)->label == "VP") {
				while (j < phrases.size()) {
					Node *new_bar = new Node("V'", phrases.at(i)->left, phrases.at(j));
					phrases.at(i)->left = new_bar;

					j++;
				}
			}
			else if (phrases.at(i)->label == "AdjP") {
				while (j > 0 && phrases.at(j)->label != "DP") {
					j--;
					if (phrases.at(j)->label == "AdvP") {
						Node *new_bar = new Node("Adj'", phrases.at(i)->left, phrases.at(j));
						phrases.at(i)->left = new_bar;
					}
				}
			}
		}
	}

	Node *BinaryTree::create_phrase(string tag) {
		Node *head = new Node(tag);
		Node *bar = new Node(tag + "'", head);
		Node *phrase = new Node(tag + "P", bar);

		return phrase;
	}
}