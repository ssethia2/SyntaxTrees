#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void windowResized(int w, int h);
		void gotMessage(ofMessage msg);
		
};
