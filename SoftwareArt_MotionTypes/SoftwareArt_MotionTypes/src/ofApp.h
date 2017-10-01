#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	ofxPanel guiPanel;

	// TRIG
	ofxVec3Slider trig;

	// LERP
	ofxVec3Slider lerp;
	bool reverse = false;

	// MOD
	ofxVec3Slider mod;


	vector<float> movement;
	vector<ofxVec3Slider> params;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
