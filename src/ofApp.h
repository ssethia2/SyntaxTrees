#pragma once

#include "ofMain.h"
#include "../tree_gen.h"

using std::string;

enum ProjectState {
	TAKE_INPUT,
	DRAW_TREE,
	RESET
};

class ofApp : public ofBaseApp {

public:
	ProjectState current_state_ = TAKE_INPUT;

	string syntax_;
	
	ofTrueTypeFont prompt_font_;
	ofTrueTypeFont user_font_;

	void setup();
	void update();
	void draw();
	void drawTree(BinaryTree::Node *root, int i, int j, int count, int offset);

	void keyPressed(int key);

	void reset();
};