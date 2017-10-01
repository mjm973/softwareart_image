#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	for (int i = 0; i < 3; ++i) {
		movement.push_back(0);
	}

	guiPanel.setup("Params");
	guiPanel.add(trig.setup("Trig", ofVec3f(100, 1, 0), ofVec3f(0, 0, 0), ofVec3f(ofGetHeight(), 10, TWO_PI)));
	guiPanel.add(lerp.setup("Lerp", ofVec3f(100, 0.5, 0), ofVec3f(0, 0, 0), ofVec3f(ofGetHeight(), 1, TWO_PI)));
	guiPanel.add(mod.setup("Mod", ofVec3f(100, 1, 0), ofVec3f(0, 0, 0), ofVec3f(ofGetHeight(), 10, TWO_PI)));

	params.push_back(trig);
	params.push_back(lerp);
	params.push_back(mod);
}

//--------------------------------------------------------------
void ofApp::update(){
	// TRIG
	movement[0] = 0.5 + 0.5*sin(ofGetElapsedTimef()*params[0]->y); // pass in time in seconds

	// LERP
	float end = reverse ? 0 : 1;
	movement[1] = ofLerp(movement[1], end, (params[1]->y)*0.01);
	if (abs(movement[1] - end) < 0.01) {
		reverse = !reverse;
	}

	// MOD
	movement[2] = ofGetElapsedTimef()*params[2]->y;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);

	float yPos = 0;
	for (int i = 0; i < movement.size(); ++i) {
		ofSetColor(ofColor::fromHsb(i * 255 / movement.size(), 255, 255));

		yPos = movement[i] * params[i]->x;
		if (i == 2) {
			yPos = (int)yPos%(int)params[2]->x;
		}
		ofDrawRectangle(300 + 100 * i, yPos, 50, 50);
	}

	guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
