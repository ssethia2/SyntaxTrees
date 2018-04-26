#pragma once

#include "ofMain.h"

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
	ofTrueTypeFont font_;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void reset();
};