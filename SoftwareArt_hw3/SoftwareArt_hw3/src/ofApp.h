#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// Normal Distribution Generator taken from StackOverflow:
// (https://stackoverflow.com/questions/28618900/c-generate-random-numbers-following-normal-distribution-within-range)
#include <random>

class Generator {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
	double min;
	double max;
public:
	Generator(double mean, double stddev, double min, double max) :
		distribution(mean, stddev), min(min), max(max)
	{}

	double operator ()() {
		while (true) {
			double number = this->distribution(generator);
			if (number >= this->min && number <= this->max)
				return number;
		}
	}
};

// End of borrowed code

class Wave {
	float theta = 0;
	float amplitude = 0;
	float frequency = 0;
	float phaseShift = 0;

	bool bLastNoise = false;

	int resolution = 300;
	vector<float> values;

	static Generator gen;

	//float noiseSeed = ofRandomf();
	float seed = ofRandomf();
	float noiseOff = 0;

	bool bTime = false;
	bool bNoise = false;
	float noiseStepMult = 1;

public:
	Wave();

	void setFlags(bool bTime, bool bNoise);
	bool update(ofVec3f params);
	bool update(ofVec4f paramsPlus);
	bool update(float _amp, float _freq, float _shift);
	void recalc();
	void assign(vector<float> _vals);
	void draw(int mode, bool bColor, bool bVisible = true, bool bFill = false, int alpha = 255);

	static Wave sum(vector<Wave*> waves);
};

class ofApp : public ofBaseApp {

	ofxPanel guiPanel;

	ofxToggle bSum;
	ofxToggle bColors;
	ofxToggle bFill;
	ofxSlider<float> alpha;
	ofxToggle bPerlin;

	ofxToggle bAnimTime;
	ofxToggle bAnimNoise;

	ofxSlider<int> mode;

	ofxVec4Slider wave1;
	ofxVec4Slider wave2;
	ofxVec4Slider wave3;
	ofxVec4Slider wave4;
	ofxVec4Slider wave5;

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


