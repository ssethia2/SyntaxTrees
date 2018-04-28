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
		Node *test_phrase = empty.create_phrase("N");
		REQUIRE(test_phrase->label == "NP");
		REQUIRE(test_phrase->left->label == "N'");
		REQUIRE(test_phrase->left->left->label == "N");
		REQUIRE(test_phrase->right == nullptr);
	}

	TEST_CASE("Vector constructor") {
		vector<string> n = {"D", "N"};
		BinaryTree one_phrase = BinaryTree::BinaryTree(n);
		REQUIRE(one_phrase.root_->label == "DP");
	}
}