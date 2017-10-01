#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	goal = Goal(ofGetWidth()*0.5, ofGetHeight()*0.5);

	guiPanel.setup("floop");
	guiPanel.add(dest.setup("Destination", ofVec2f(ofGetWidth()*0.5, ofGetHeight()*0.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
	guiPanel.add(dist.setup("Distance", 5, 0.1, 20));
}

//--------------------------------------------------------------
void ofApp::update() {
	goal.setDestination(dest);
	goal.setDistance(dist);

	goal.chase();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	goal.visualize();

	guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Goal::Goal() {
	Goal(0, 0);
}

Goal::Goal(float _x, float _y) {
	initialDestination = ofVec2f(_x, _y);
	distance = 5;
}

Goal::Goal(ofVec2f dest) {
	initialDestination = dest;
	distance = 5;
}

void Goal::setDestination(ofVec2f dest) {
	destination = dest;
}

void Goal::setDistance(float dist) {
	distance = dist;
}

void Goal::chase() {
	time += 0.005;
	if (time >= 1) {
		time = 0;
	}

	ofVec2f changeOfdestination = 200 * ofVec2f(ofSignedNoise(startingPoint.x + change), ofSignedNoise(startingPoint.y + change));
	ofVec2f newDestination = initialDestination + changeOfdestination;
	setDestination(newDestination);

	float newDistance = ofLerp(5, 10, ofNoise(startingFarness + change));
	setDistance(newDistance);

	change += 0.001;
}

void Goal::visualize() {
	float light = 0;

	float size = 600;
	float actualSize = size;

	float step = (1 - 1 / distance);
	float destStep = 0;

	float lerpSize = 0;

	float iter = log(0.1 / 600) / log(step);

	ofVec2f center = ofVec2f(ofGetWidth() *0.5, ofGetHeight()*0.5);

	for (int i = 0; i < iter; ++i) {
		destStep = i / iter;

		ofPushMatrix();

		//center = center.getInterpolated(destination, step);

		ofTranslate(center.getInterpolated(destination, destStep));

		lerpSize = (size / step) - size;
		actualSize = size + ofLerp(0, lerpSize, time);
		light = 255 * (1 - actualSize / 600);

		ofSetColor(light);
		ofDrawCircle(0, 0, actualSize);

		size *= step;

		ofPopMatrix();
	}
}
