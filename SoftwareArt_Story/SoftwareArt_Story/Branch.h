#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Branch {
	ofVec2f pos;
	ofVec2f end;
	float theta;
	float length;

	Branch* parent;
	vector<Branch*> children;

public:
	Branch();
	Branch(ofVec2f _pos, float _theta, float _length);

	void setParent(Branch* parent);
	void setLength(float len);

	void split();
	void draw();
	void kill();

	static float probability;
	static float ratio;
	static float deltaAngle;
};