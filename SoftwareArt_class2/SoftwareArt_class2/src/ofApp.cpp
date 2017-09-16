#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup("color"); // create gui panel and give it a title
	gui.add(hue.setup("hue", 100, 0, 255)); // initialize sider and attach to gui panel
	gui.add(saturation.setup("saturation", 200, 0, 255)); // ditto
	gui.add(brightness.setup("brightness", 200, 0, 255)); // ditto

	gui.add(radius.setup("radius", 100, 0, 500));
	gui.add(bluntness.setup("bluntness", 1, 0.5, 2.5));
	gui.add(offX.setup("x offset", 200, 0, ofGetWidth()));
	gui.add(offY.setup("y offset", 200, 0, ofGetHeight()));

	randomSeed = ofRandomf();
}

//--------------------------------------------------------------
void ofApp::update() {
	bgColor.setHsb(hue, saturation, brightness);
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (bSave) {
		ofBeginSaveScreenAsPDF("blob.pdf");
	}
	ofBackground(bgColor);

	ofPushMatrix();
	ofTranslate(offX, offY);
	ofBeginShape();

	float rad = 0;
	for (float i = 0; i < TWO_PI; i += 0.01f) {
		rad = radius * (bluntness + ofNoise(cos(i) + randomSeed, sin(i) + randomSeed)) / (2*bluntness);
		ofVertex(rad*cos(i), rad*sin(i));
	}
	ofEndShape(true);
	ofPopMatrix();
	if (bSave) {
		ofEndSaveScreenAsPDF();
	}
	bSave = false;

	gui.draw(); // draw the gui!
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
	switch (button) {
	case 1:
		bSave = true;
		break;
	case 2:
		randomSeed = ofRandomf();
		break;
	}
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
