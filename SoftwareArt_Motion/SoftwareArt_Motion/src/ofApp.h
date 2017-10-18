#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Slash {

private:
	ofVec3f position;
	int index;

	static ofMesh s0;
	static ofMesh s1;
	static ofMesh s2;
	static ofMesh s3;
	static ofMesh s4;
	static ofMesh s5;

	static ofMesh makeMesh(ofVec3f v1, ofVec3f v2, ofVec3f v3, ofVec3f v4);

public:
	static float size;

	Slash();
	Slash(int x, int y, int z);
	void reroll();
	void update();
	void display();
};

class ofApp : public ofBaseApp {

	ofxPanel gui;
	ofxSlider<int> resolution;
	ofxToggle pauseScroll;
	ofxToggle pauseRotation;
	int prevResolution = 0;

	vector<vector<vector<Slash>>> matrix;

	int xNow = 0;
	int yNow = resolution - 1;
	int zNow = 0;

	ofCamera cam;
	float theta = 0;

	ofTrueTypeFont c64;

	bool bSave = false;

public:
	static ofColor c64bg;
	static ofColor c64type;

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

	void prepareMatrix(int res);
	void drawFrame();
	void drawText();
};
