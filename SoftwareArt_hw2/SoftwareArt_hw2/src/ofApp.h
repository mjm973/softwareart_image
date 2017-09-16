#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Wave {

	float amplitude = 0;
	float frequency = 0;
	float phaseShift = 0;

	bool bLastNoise = false;

	int resolution = 300;
	vector<float> values;
	//float t;

public:
	Wave();

	float seed = ofRandomf();

	bool update(ofVec3f params, bool bNoise = false);
	bool update(float _amp, float _freq, float _shift, bool bNoise = false);
	void recalc(bool bNoise = false);
	void assign(vector<float> _vals);
	void draw(int mode, bool bColor, bool bVisible = true, bool bFill = false, int alpha = 255);

	static Wave sum(vector<Wave*> waves);
};

class ofApp : public ofBaseApp{

	ofxPanel guiPanel;

	ofxToggle bSum;
	ofxToggle bColors;
	ofxToggle bFill;
	ofxSlider<float> alpha;
	ofxToggle bPerlin;
	ofxSlider<int> mode;

	ofxVec3Slider wave1;
	ofxVec3Slider wave2;
	ofxVec3Slider wave3;
	ofxVec3Slider wave4;
	ofxVec3Slider wave5;
	
	vector<Wave*> waves;
	Wave sum;

	bool bSumModified = false;
	bool bSave = false;

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


