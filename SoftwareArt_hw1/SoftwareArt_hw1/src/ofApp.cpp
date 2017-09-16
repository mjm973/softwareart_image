#include "ofApp.h"
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "fak" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	color1();
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

// ---------------------------------------
void ofApp::color1() {
	array<int, 7> hues = { 0, 120, 80, 200, 160, 280, 240 };
	ofColor col = ofColor::fromHsb(0, 255, 255);
	float width = ofGetWidth() / hues.size();

	for (int i = 0; i < hues.size(); ++i) {
		col.setHue(hues[i]);
		ofDrawRectangle(i*width, 0, width, ofGetHeight());
	}

}

void ofApp::color2() {

}

void ofApp::shape1() {

}

void ofApp::shape2() {

}

void ofApp::dual1() {

}

void ofApp::dual2() {

}
