#include "ofApp.h"

//--------------------------------------------------------------
ofColor ofApp::c64bg = ofColor(66, 66, 229);

ofColor ofApp::c64type = ofColor(165, 165, 255);

void ofApp::setup() {
	gui.setup("floop");
	gui.add(resolution.setup("Resolution", 6, 1, 15));
	gui.add(pauseScroll.setup("Pause Scroll", false));
	gui.add(pauseRotation.setup("Pause Rotation", false));

	cam.setFov(75);

	prepareMatrix(resolution);

	c64.load("C64_Pro_Mono-STYLE.ttf", 16);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (resolution != prevResolution) {
		prepareMatrix(resolution);
	}
	else if (!pauseScroll) {
		matrix[zNow][yNow][xNow].reroll();

		if (++xNow >= resolution) {
			xNow = 0;
			if (--yNow < 0) {
				yNow = resolution - 1;
				if (++zNow >= resolution) {
					zNow = 0;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();

	ofBackground(c64bg);

	ofPushMatrix();
	ofTranslate(0, 0, -1200);
	ofRotateY(theta);

	if (!pauseRotation) {
		theta += 0.05;
	}

	for (int z = 0; z < resolution; ++z) {
		for (int y = 0; y < resolution; ++y) {
			for (int x = 0; x < resolution; ++x) {
				matrix[z][y][x].display();
			}
		}
	}

	ofPopMatrix();

	cam.end();

	ofSetColor(c64type);

	drawFrame();
	drawText();

	if (bSave) {
		ofSaveFrame(true);
	}
	else
	{
		gui.draw();
	}

	bSave = false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case ' ':
		bSave = true;
	}
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

// -----------------------------------------------------

void ofApp::prepareMatrix(int res) {
	matrix.clear();
	matrix.resize(resolution);

	Slash::size = 750 / resolution;
	float s = Slash::size;

	Slash current = Slash(0, 0, 0);
	float curX = 0;
	float curY = 0;
	float curZ = 0;
	for (int z = 0; z < resolution; ++z) {
		matrix[z].resize(resolution);
		curZ = +s * (z - resolution*0.5);
		for (int y = 0; y < resolution; ++y) {
			curY = /*ofGetHeight()*0.5 + */s * (y - resolution*0.5);
			matrix[z][y].resize(resolution);
			for (int x = 0; x < resolution; ++x) {
				curX = /*ofGetWidth()*0.5 +*/ s * (x - resolution*0.5);
				current = Slash(curX, curY, curZ);
				matrix[z][y][x] = current;
			}
		}
	}

	xNow = 0;
	yNow = resolution - 1;
	zNow = 0;

	prevResolution = resolution;
}

void ofApp::drawFrame() {
	ofDrawRectangle(0, 0, ofGetWidth(), 50);
	ofDrawRectangle(0, ofGetHeight() - 50, ofGetWidth(), 50);
	ofDrawRectangle(0, 0, 50, ofGetHeight());
	ofDrawRectangle(ofGetWidth() - 50, 0, 50, ofGetHeight());
}

void ofApp::drawText() {
	c64.drawString("   ****   COMMODORE 2017   ****", 80, 84);

	char str[255];
	int res = resolution;
	sprintf(str, "100 PRINT - RUNNING: RESOLUTION %d", res);
	c64.drawString(str, 80, ofGetHeight() - 70);
}

// ././././././././././././../././././

Slash::Slash() {
	Slash(0, 0, 0);
}

Slash::Slash(int x, int y, int z) {
	position = ofVec3f(x, y, z);
	index = -1;
}

float Slash::size = 50;

void Slash::reroll() {
	//index = -2;
	index = floor(ofRandom(6));
}

void Slash::update() {
	position.z += size / 60;
}

void Slash::display() {
	ofPushMatrix();
	ofTranslate(position);
	ofScale(size, size, size);

	switch (index) {
	case -1:

		break;
	case 0:
		s0.draw();
		break;
	case 1:
		s1.draw();
		break;
	case 2:
		s2.draw();
		break;
	case 3:
		s3.draw();
		break;
	case 4:
		s4.draw();
		break;
	case 5:
		s5.draw();
		break;
	default:
		ofDrawRectangle(0, 0, 0, size, size);
		break;
	}
	ofPopMatrix();
}

ofMesh Slash::makeMesh(ofVec3f v1, ofVec3f v2, ofVec3f v3, ofVec3f v4) {
	ofMesh mesh;
	//ofColor col = ofColor(27, 234, 183, 60);
	//ofColor col = ofColor(66, 66, 229, 60);
	ofColor col = ofColor(165, 165, 255, 60);

	mesh.addVertex(v1);
	mesh.addColor(col);
	mesh.addVertex(v2);
	mesh.addColor(col);
	mesh.addVertex(v3);
	mesh.addColor(col);
	mesh.addVertex(v4);
	mesh.addColor(col);
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

	return mesh;
}

ofMesh Slash::s0 = makeMesh(ofVec3f(), ofVec3f(1, 1, 0), ofVec3f(1, 1, 1), ofVec3f(0, 0, 1));

ofMesh Slash::s1 = makeMesh(ofVec3f(0, 1, 0), ofVec3f(1, 0, 0), ofVec3f(1, 0, 1), ofVec3f(0, 1, 1));

ofMesh Slash::s2 = makeMesh(ofVec3f(), ofVec3f(1, 0, 0), ofVec3f(1, 1, 1), ofVec3f(0, 1, 1));

ofMesh Slash::s3 = makeMesh(ofVec3f(0, 1, 0), ofVec3f(1, 1, 0), ofVec3f(1, 0, 1), ofVec3f(0, 0, 1));

ofMesh Slash::s4 = makeMesh(ofVec3f(), ofVec3f(1, 0, 1), ofVec3f(1, 1, 1), ofVec3f(0, 1, 0));

ofMesh Slash::s5 = makeMesh(ofVec3f(0, 0, 1), ofVec3f(1, 0, 0), ofVec3f(1, 1, 0), ofVec3f(0, 1, 1));
