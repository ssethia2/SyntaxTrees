#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/tree_gen.h"

using std::vector;
using std::string;

namespace BinaryTree {
	TEST_CASE("Default constructor") {
		BinaryTree empty = BinaryTree::BinaryTree();
		REQUIRE(empty.count() == 0);
	}

	TEST_CASE("Create phrase") {
		BinaryTree empty = BinaryTree::BinaryTree();
		Node *test_phrase = empty.CreatePhrase("N");

		REQUIRE(test_phrase->label == "NP");
		REQUIRE(test_phrase->left->label == "N'");
		REQUIRE(test_phrase->left->left->label == "N");
		REQUIRE(test_phrase->right == nullptr);
	}

	/*TEST_CASE("Vector constructor") {
		vector<string> n = {"D", "N"};
		BinaryTree one_phrase = BinaryTree::BinaryTree(n);
		REQUIRE(one_phrase.root_->label == "DP");
	}*/

	TEST_CASE("DPhrase with immediately following NP test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<Node*> test_phrases = {};

		test_phrases.push_back(empty.CreatePhrase("D"));
		test_phrases.push_back(empty.CreatePhrase("N"));

		REQUIRE(test_phrases.at(0)->label == "DP");

		empty.DPhrase(test_phrases, 0, 0);
		REQUIRE(test_phrases.at(0)->label == "DP");
		REQUIRE(test_phrases.at(0)->left->right->label == "NP");
	}

	TEST_CASE("DPhrase with DP NP separated test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<Node*> test_phrases = {};

		test_phrases.push_back(empty.CreatePhrase("D"));
		test_phrases.push_back(empty.CreatePhrase("AdJ"));
		test_phrases.push_back(empty.CreatePhrase("N"));

		REQUIRE(test_phrases.at(0)->label == "DP");

		empty.DPhrase(test_phrases, 0, 0);
		REQUIRE(test_phrases.at(0)->label == "DP");
		REQUIRE(test_phrases.at(0)->left->right->label == "NP");
	}

	TEST_CASE("NPhrase with no adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<Node*> test_phrases = {};

		test_phrases.push_back(empty.CreatePhrase("D"));
		test_phrases.push_back(empty.CreatePhrase("N"));
		test_phrases.push_back(empty.CreatePhrase("V"));

		empty.NPhrase(test_phrases, 1, 1);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(1)->label == "NP");
		REQUIRE(test_phrases.at(1)->left->right == nullptr);
	}

	TEST_CASE("NPhrase with preceding AdjP test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<Node*> test_phrases = {};

		test_phrases.push_back(empty.CreatePhrase("D"));
		test_phrases.push_back(empty.CreatePhrase("Adj"));
		test_phrases.push_back(empty.CreatePhrase("N"));

		empty.NPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(1)->label == "AdjP");
		REQUIRE(test_phrases.at(2)->label == "NP");
		REQUIRE(test_phrases.at(2)->left->label == "N'");
		REQUIRE(test_phrases.at(2)->left->left->label == "AdjP");
	}

	TEST_CASE("NPhrase with following PP test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<Node*> test_phrases = {};

		test_phrases.push_back(empty.CreatePhrase("D"));
		test_phrases.push_back(empty.CreatePhrase("N"));
		test_phrases.push_back(empty.CreatePhrase("P"));

		empty.NPhrase(test_phrases, 1, 1);
		REQUIRE(test_phrases.at(2)->label == "PP");
		REQUIRE(test_phrases.at(1)->label == "NP");
		REQUIRE(test_phrases.at(1)->left->right->label == "PP");
	}

	TEST_CASE("NPhrase with preceding and following adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "Adj", "N", "P"};
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.NPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "NP");
		REQUIRE(test_phrases.at(2)->left->left->label == "N'");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "AdjP");
		REQUIRE(test_phrases.at(2)->left->right->label == "PP");
	}
}