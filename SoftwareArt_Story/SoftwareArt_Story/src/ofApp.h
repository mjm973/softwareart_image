#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "../Branch.h"
#include "../Bullet.h"
#include "../Spawner.h"

class ofApp : public ofBaseApp {

	ofxPanel mainGui;
	ofxSlider<int> currentScene;

	ofxSlider<int> mainRate;
	ofxSlider<float> mainPeriod;
	ofxSlider<float> mainLife;
	ofxVec4Slider mainParam;

	int rate = 1;
	float period = 1;
	float life = 1;
	ofVec4f param = ofVec4f();

	int pRate = 1;
	float pPeriod = 1;
	float pLife = 1;
	ofVec4f pParam = ofVec4f();

	int cRate = 1;
	float cPeriod = 1;
	float cLife = 1;
	ofVec4f cParam = ofVec4f();

	bool playback = false;
	int scene = 0;
	int prevScene = -1;

	Spawner spawner;

	enum Scene {
		seed,
		roots,
		rain,
		sprout,
		sun,
		flower,
		wind
	};

public:
	void setup();
	void update();
	void draw();

	void setScene();
	void sceneChanged();
	void guiChanged();

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
