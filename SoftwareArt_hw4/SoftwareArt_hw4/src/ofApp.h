#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Goal {
private:
	ofVec2f destination;
	ofVec2f initialDestination;

	float distance;
	float time = 0;
	float change = 0;
	ofVec2f startingPoint = ofVec2f(ofRandomf(), ofRandomf());
	float startingFarness = ofRandomf();

public:
	Goal();
	Goal(float _x, float _y);
	Goal(ofVec2f _pos);

	void setDestination(ofVec2f dest);
	void setDistance(float dist);
	void chase();
	void visualize();
};

class ofApp : public ofBaseApp {


public:
	Goal goal;

	ofxPanel guiPanel;
	ofxVec2Slider dest;
	ofxSlider<float> dist;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
