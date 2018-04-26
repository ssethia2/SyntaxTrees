#include "ofApp.h"
#include "../tree_gen.h"

//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	std::vector<string> tags = {"D", "N", "V", "D", "N", "P", "D", "N"};
	BinaryTree::BinaryTree syntax_tree = BinaryTree::BinaryTree(tags);
	int x = syntax_tree.count();
	for (int i = 1; i <= x; i++) {
		ofDrawCircle(ofGetWidth() / 2, i*ofGetHeight() / x - 350 / x, 200 / x);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}