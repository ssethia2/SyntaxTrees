#include "ofApp.h"
#include "math.h"


using std::string;
using std::vector;

//--------------------------------------------------------------
void ofApp::setup() {
	syntax_ = "";
	ofBackground(0);
	prompt_font_.load("itcblkad.ttf", 28);
	user_font_.load("itcblkad.ttf", 22);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (current_state_ == TAKE_INPUT) {
		prompt_font_.drawString("Enter your input below. Press return to draw tree.", ofGetWidth()/2, ofGetHeight()/1.5);
		user_font_.drawString(syntax_, ofGetWidth() / 2 + 10, ofGetHeight() / 1.5 + 30);
	}

	if (current_state_ == DRAW_TREE) {
		/*std::vector<string> tags = {"D", "N", "V", "D", "N", "P", "D", "N"};
		BinaryTree::BinaryTree syntax_tree = BinaryTree::BinaryTree(tags);*/
		int x = pow(2.0, 4.0) - 1;
		for (int i = 0; i < log2(x); i++) {
			for (int j = 1; j <= pow(2.0, i); j++) {
				ofDrawCircle(j * ofGetWidth() / (pow(2.0, i + 1) + 2.0), (i + 2)*ofGetHeight() / x, 250 / x);
			}
		}

		prompt_font_.drawString("Press R to reset.", 500, 500);
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