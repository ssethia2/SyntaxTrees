#include "ofApp.h"
#include "math.h"
#include "../tree_gen.h"


using std::string;
using std::vector;

//--------------------------------------------------------------
void ofApp::setup() {
	syntax_ = "";
	ofSetFullscreen(true);
	ofBackground(50);
	prompt_font_.load("itcblkad.ttf", 28);
	user_font_.load("itcblkad.ttf", 22);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (current_state_ == TAKE_INPUT) {
		prompt_font_.drawString("Enter pos tags with spaces below. Press return to draw tree.", ofGetWidth() / 3, ofGetHeight() / 1.2);
		user_font_.drawString(syntax_, ofGetWidth() /3 + 10, ofGetHeight() / 1.2 + 30);
	}

	if (current_state_ == DRAW_TREE) {
		vector<string> tags;
		string word;
		syntax_ += " ";
		for (char &tag : syntax_) {
			string s(1, tag);
			if (s != " " && tag != '\0' && tag != '\x2') {
				word += (s);
			}
			if (s == " ") {
				tags.push_back(word);
				word = "";
			}
		}

		BinaryTree::BinaryTree syntax_tree = BinaryTree::BinaryTree(tags);

		int count = 0;
		count = syntax_tree.count();

		int x = 0;
		while (pow(2.0, x) < count) {
			x++;
		}

		/*for (int i = 0; i < x; i++) {
			for (int j = 1; j <= pow(2.0, i); j++) {
				ofDrawCircle(j * ofGetWidth() / (pow(2.0, i + 1) + 2.0), (i + 1)*ofGetHeight() / pow(1.5, x), 500 / pow(2.0, x));
			}
		}*/

		drawTree(syntax_tree.root_, 0, -4, x);

		prompt_font_.drawString("Press R to reset, Esc to exit", ofGetWidth() / 3, ofGetHeight() / 1.2);
	}
}

void ofApp::drawTree(BinaryTree::Node *root, int i, int j, int count) {
	double width = (ofGetWidth() / 2.0) + j * 35;
	double height = ofGetHeight() / 4 + i * 50;
	ofDrawCircle(width + 7, height - 5, 17);
	ofDrawBitmapStringHighlight(root->label, width, height, ofColor::white, ofColor::black);

	if (root->left && !(root->right)) {
		i++;
		ofDrawLine(width + 7, height, width + 7, ofGetHeight() / 4 + i * 50);
		drawTree(root->left, i, j, count);
	} else if (root->left) {
		ofDrawLine(width + 7, height, (ofGetWidth() / 2.0) + ((j - (count - i) - 1) * 35) + 7, ofGetHeight() / 4 + (i + 1) * 50);
		drawTree(root->left, i + 1, j - (count - i) - 1, count);
	}
	if (root->right) {
		ofDrawLine(width + 7, height, (ofGetWidth() / 2.0) + ((j + (count - i) + 1) * 35) + 7, ofGetHeight() / 4 + (i + 1) * 50);
		drawTree(root->right, i + 1, j + (count - i) + 1, count);
	}
}

//--------------------------------------------------------------
void ofApp::reset() {
	syntax_ = "";
	current_state_ = TAKE_INPUT;
}

void ofApp::keyPressed(int key) {
	if (current_state_ == TAKE_INPUT) {
		if (key == OF_KEY_BACKSPACE && syntax_.size() > 0) { // backspace
			syntax_ = syntax_.substr(0, syntax_.size() - 1); // delete one character
		}
		else if (key == OF_KEY_RETURN && syntax_.size() > 0) {
			current_state_ = DRAW_TREE;
		}
		else {
			syntax_.append(1, (char)key);
		}
	}
	if (current_state_ == DRAW_TREE) {
		if (toupper(key) == 'R') {
			reset();
		}
	}
}