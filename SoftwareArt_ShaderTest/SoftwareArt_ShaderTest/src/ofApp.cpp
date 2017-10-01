#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// OF
	// >> COMPILES

	// VERTEX SHADER
	// >> SAYS WHERE STUFF IS

	// FRAGMENT SHADER
	// >> SAYS WHAT STuFF SHOULD LOOK LIKE


	shader.load("shader.vert", "shader.frag");

	plane.set(500, 500, 100, 100);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);

	shader.begin();

	//shader.setUniform1f("uTime", ofGetElapsedTimef());

	plane.draw();

	//ofDrawRectangle(0, 0, 500, 500);
	shader.end();
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
