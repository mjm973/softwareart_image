#include "Branch.h"

Branch::Branch() {
	Branch(ofVec2f::zero(), 0.0, 10.0);
}

Branch::Branch(ofVec2f _pos, float _theta, float _length) {
	pos = _pos;
	theta = _theta;
	length = _length;

	end = ofVec2f(cos(theta), sin(theta))*length;

	parent = NULL;
}

void Branch::setParent(Branch* _parent) {
	parent = _parent;
}

void Branch::setLength(float len) {
	length = len;
	end = ofVec2f(cos(theta), sin(theta))*length;
}

void Branch::split() {
	if (length < 5) {
		return;
	}

	if (children.size() > 0) {
		for each (Branch* b in children) {
			b->split();
		}
	}
	else {
		float dart = ofRandomf();

		Branch* next = NULL;
		if (dart < probability) {
			next = new Branch(pos + end, theta + ofRandom(-deltaAngle, deltaAngle), length*ratio);
			next->setParent(this);
			children.push_back(next);
		}

		next = new Branch(pos + end, theta + ofRandom(-deltaAngle, deltaAngle), length*ratio);
		next->setParent(this);
		children.push_back(next);
	}
}

void Branch::draw() {
	if (length < 5) {
		return;
	}

	ofPushMatrix();
	ofTranslate(pos);
	ofDrawLine(ofVec2f(0, 0), end);
	ofPopMatrix();

	if (children.size() > 0) {
		for each (Branch* b in children) {
			b->draw();
		}
	}
}

void Branch::kill() {
	int size = children.size();

	if (size > 0) {
		for (int i = size - 1; i >= 0; --i) {
			children[i]->kill();
			delete children[i];
		}

		children.clear();
	}
}

float Branch::probability = 0;

float Branch::ratio = 0.5;

float Branch::deltaAngle = PI / 4;