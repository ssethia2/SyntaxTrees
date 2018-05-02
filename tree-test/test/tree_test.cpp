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
		test_phrases.push_back(empty.CreatePhrase("V"));

		empty.NPhrase(test_phrases, 1, 1);
		REQUIRE(test_phrases.at(2)->label == "PP");
		REQUIRE(test_phrases.at(1)->label == "NP");
		REQUIRE(test_phrases.at(1)->left->right->label == "PP");
	}

	TEST_CASE("NPhrase with preceding and following adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "Adj", "N", "P", "V" };
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

	TEST_CASE("NPhrase with multiple preceding adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "Adj", "Adj", "N", "V" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.NPhrase(test_phrases, 3, 3);
		REQUIRE(test_phrases.at(3)->label == "NP");
		REQUIRE(test_phrases.at(3)->left->label == "N'");
		REQUIRE(test_phrases.at(3)->left->left->label == "AdjP");
		REQUIRE(test_phrases.at(3)->left->right->label == "N'");
		REQUIRE(test_phrases.at(3)->left->right->left->label == "AdjP");
		REQUIRE(test_phrases.at(3)->left->right->right->label == "N'");
		REQUIRE(test_phrases.at(3)->left->right->right->left->label == "N");
	}

	TEST_CASE("NPhrase with multiple preceding and following adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "Adj", "Adj", "N", "P", "P", "V" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.NPhrase(test_phrases, 3, 3);
		REQUIRE(test_phrases.at(3)->label == "NP");
		REQUIRE(test_phrases.at(3)->left->label == "N'");
		REQUIRE(test_phrases.at(3)->left->right->label == "PP");
		REQUIRE(test_phrases.at(3)->left->left->label == "N'");
		REQUIRE(test_phrases.at(3)->left->left->right->label == "PP");
		REQUIRE(test_phrases.at(3)->left->left->left->label == "N'");
		REQUIRE(test_phrases.at(3)->left->left->left->left->label == "AdjP");
		REQUIRE(test_phrases.at(3)->left->left->left->right->label == "N'");
		REQUIRE(test_phrases.at(3)->left->left->left->right->left->label == "AdjP");
		REQUIRE(test_phrases.at(3)->left->left->left->right->right->label == "N'");
		REQUIRE(test_phrases.at(3)->left->left->left->right->right->left->label == "N");
	}

	TEST_CASE("VPhrase with one following D adjuncts") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.VPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(2)->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "V");
	}

	TEST_CASE("VPhrase with one following D multiple Adv adjuncts") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D", "Adv", "Adv" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.VPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(2)->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->right->label == "AdvP");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->right->label == "AdvP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->left->label == "V");
	}

	TEST_CASE("VPhrase with multiple following adjuncts") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D", "N", "P" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.VPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(2)->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->right->label == "PP");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->label == "V");
	}

	TEST_CASE("VPhrase with phrases following P which shouldn't be added") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D", "N", "P", "D", "D" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.VPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(2)->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->right->label == "PP");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->label == "V");
	}

	TEST_CASE("VPhrase with multiple following P and D phrases") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D", "N", "P", "D", "D", "P", "D" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.VPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "VP");
		REQUIRE(test_phrases.at(2)->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->right->label == "PP");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->right->label == "PP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->label == "V'");
		REQUIRE(test_phrases.at(2)->left->left->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->left->left->left->label == "V");
	}

	TEST_CASE("PPhrase test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "P", "D", "Adj", "N" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.PPhrase(test_phrases, 2, 2);
		REQUIRE(test_phrases.at(2)->label == "PP");
		REQUIRE(test_phrases.at(2)->left->label == "P'");
		REQUIRE(test_phrases.at(2)->left->left->label == "P'");
		REQUIRE(test_phrases.at(2)->left->right->label == "DP");
		REQUIRE(test_phrases.at(2)->left->left->left->label == "P");
	}

	TEST_CASE("AdjPhrase with multiple preceding adjuncts test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "Adv", "Adv", "Adv", "Adj" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.AdjPhrase(test_phrases, 4, 4);
		REQUIRE(test_phrases.at(4)->label == "AdjP");
		REQUIRE(test_phrases.at(4)->left->label == "Adj'");
		REQUIRE(test_phrases.at(4)->left->left->label == "AdvP");
		REQUIRE(test_phrases.at(4)->left->right->label == "Adj'");
		REQUIRE(test_phrases.at(4)->left->right->left->label == "AdvP");
		REQUIRE(test_phrases.at(4)->left->right->right->label == "Adj'");
		REQUIRE(test_phrases.at(4)->left->right->right->left->label == "AdvP");
		REQUIRE(test_phrases.at(4)->left->right->right->right->label == "Adj");
	}

	TEST_CASE("CPhrase with only subject test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.CPhrase(test_phrases);
		REQUIRE(empty.root_->label == "S");
		REQUIRE(empty.root_->left->label == "DP");
	}

	TEST_CASE("CPhrase with only predicate test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "V", "Adv" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.CPhrase(test_phrases);
		REQUIRE(empty.root_->label == "S");
		REQUIRE(empty.root_->right->label == "VP");
	}

	TEST_CASE("CPhrase with both subject and predicate test") {
		BinaryTree empty = BinaryTree::BinaryTree();
		vector<string> tags = { "D", "N", "V", "D", "N", "Adv" };
		vector<Node*> test_phrases = {};

		for (auto tag : tags) {
			test_phrases.push_back(empty.CreatePhrase(tag));
		}

		empty.BuildTree(test_phrases);
		REQUIRE(empty.root_->label == "S");
		REQUIRE(empty.root_->left->label == "DP");
		REQUIRE(empty.root_->right->label == "VP");
		REQUIRE(empty.root_->left->left->right->label == "NP");
		REQUIRE(empty.root_->right->left->right->label == "AdvP");
	}

	TEST_CASE("Vector constructor") {
	vector<string> tags = {"D", "N", "V", "D", "N"};
	BinaryTree one_phrase = BinaryTree::BinaryTree(tags);

	REQUIRE(one_phrase.root_->label == "S");
	REQUIRE(one_phrase.root_->left->label == "DP");
	REQUIRE(one_phrase.root_->left->left->right->label == "NP");
	REQUIRE(one_phrase.root_->right->label == "VP");
	REQUIRE(one_phrase.root_->right->left->right->label == "DP");
	}

	TEST_CASE("Count nodes in tree") {
		vector<string> tags = { "D", "N", "V", "D", "N" };
		BinaryTree one_phrase = BinaryTree::BinaryTree(tags);

		REQUIRE(one_phrase.count() == 17);
	}
}