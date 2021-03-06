#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	guiPanel.setup("Waves");

	ofVec4f min = ofVec4f(-5, 0, 0, 0);
	ofVec4f max = ofVec4f(5, 20, TWO_PI, 10);
	guiPanel.add(bSum.setup("Add Waves?", false));
	guiPanel.add(bColors.setup("Colors?", false));
	guiPanel.add(alpha.setup("Alpha", 255, 0, 255));
	guiPanel.add(bFill.setup("Fill?", false));
	guiPanel.add(bPerlin.setup("Noise?", false));

	guiPanel.add(bAnimTime.setup("Time Anim?", false));
	guiPanel.add(bAnimNoise.setup("Noise Anim?", false));

	guiPanel.add(mode.setup("Mode", 1, 1, 8));
	guiPanel.add(wave1.setup("Wave 1", ofVec4f(1, 1, 0, 1), min, max));
	guiPanel.add(wave2.setup("Wave 2", ofVec4f(1, 2, 0, 1), min, max));
	guiPanel.add(wave3.setup("Wave 3", ofVec4f(1, 3, 0, 1), min, max));
	guiPanel.add(wave4.setup("Wave 4", ofVec4f(1, 4, 0, 1), min, max));
	guiPanel.add(wave5.setup("Wave 5", ofVec4f(1, 5, 0, 1), min, max));

	for (int i = 0; i < 5; ++i) {
		waves.push_back(new Wave());
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < waves.size(); ++i) {
		waves[i]->setFlags(bAnimTime, bAnimNoise);
	}

	bSumModified = bSumModified || waves[0]->update(wave1);
	bSumModified = bSumModified || waves[1]->update(wave2);
	bSumModified = bSumModified || waves[2]->update(wave3);
	bSumModified = bSumModified || waves[3]->update(wave4);
	bSumModified = bSumModified || waves[4]->update(wave5);

	if (bSum && (bSumModified || bAnimNoise || bAnimTime)) {
		sum = Wave::sum(waves);
	}

	bSumModified = false;
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (bSave) {
		ofBeginSaveScreenAsPDF("capture_" + ofToString(ofGetElapsedTimeMillis()) + ".pdf");
	}

	ofBackground(255);

	for (int i = 0; i < waves.size(); ++i) {
		waves[i]->draw(mode, bColors, !bSum, bFill, alpha);
	}

	if (bSum) {
		sum.draw(mode, bColors, bSum, bFill, alpha);
	}

	if (bSave) {
		ofEndSaveScreenAsPDF();
	}
	bSave = false;

	guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case ' ':
		bSave = true;
		break;
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

// ~~~~~~~~

Wave::Wave() {
	values.resize(resolution);

}

Generator Wave::gen = Generator(0, 50, -150, 150);

void Wave::setFlags(bool _bTime, bool _bNoise) {
	bTime = _bTime;
	bNoise = _bNoise;
}

bool Wave::update(float _amp, float _freq, float _shift) {
	bool bChange = false;

	if (amplitude != _amp) {
		amplitude = _amp;
		bChange = true;
	}
	if (frequency != _freq) {
		frequency = _freq;
		bChange = true;
	}
	if (phaseShift != _shift) {
		phaseShift = _shift;
		bChange = true;
	}

	if (bChange || bNoise || bTime) {
		recalc();
	}

	return bChange;
}

bool Wave::update(ofVec3f params) {
	return update(params.x, params.y, params.z);
}

bool Wave::update(ofVec4f paramsPlus) {
	noiseStepMult = paramsPlus.w;

	return update(paramsPlus.x, paramsPlus.y, paramsPlus.z);
}

void Wave::recalc() {
	values.clear();
	values.resize(resolution);

	float currentN = 0;
	float currentTheta = bTime ? theta : 0;
	float t = seed;
	float step = TWO_PI / (float)resolution;
	for (int i = 0; i < resolution; ++i) {
		currentN = bNoise ? ofSignedNoise(seed) * 4 : 1;

		values[i] = amplitude*sin(currentTheta + i*(int)frequency*step + phaseShift) * currentN;
	}
	theta += 0.01;
	seed += 0.001 * noiseStepMult;
}

void Wave::draw(int mode, bool bColor, bool bVisible, bool bFill, int alpha) {
	if (!bVisible) {
		return;
	}

	ofPushMatrix();
	ofTranslate(0, ofGetHeight() / 2);

	float currentY = 0;
	float currentX = 0;
	float currentW = 0;

	float xStep = ofGetWidth() / (float)resolution;
	for (int i = 0; i < resolution; ++i) {
		currentX = i*xStep;

		if (bFill) {
			ofFill();
		}
		else {
			ofNoFill();
		}
		ofSetColor(bColor ? ofColor::fromHsb((int)(512 * currentX / ofGetWidth()) % 256, 255, 255, alpha) : ofColor(0, alpha));

		switch (mode) {
		case 1:
			currentY = values[i] * 100;
			currentW = 20;
			ofDrawRectangle(currentX - currentW / 2, currentY - currentW / 2, currentW, currentW);

			break;
		case 2:
			currentY = 0;
			currentW = values[i] * 50;
			ofDrawRectangle(currentX - currentW / 2, currentY - currentW / 2, currentW, currentW);

			break;
		case 3:
			currentY = 0;
			currentW = values[i] * 50;
			ofDrawRectangle(currentX - currentW / 2, currentY - currentW / 2, xStep, currentW);

			break;
		case 4:
			currentY = 0;
			currentW = values[i] * 50;
			ofDrawRectangle(currentX - xStep / 2, currentY, xStep, currentW);

			break;
		case 5:
			currentY = 0;
			currentW = values[i] * 50;
			ofDrawRectangle(currentX - xStep / 2, currentY - currentW / 2, xStep, currentW);
			break;
		case 6:
			currentW = xStep;

			for (int j = 0; j < 10; ++j) {
				currentY = values[i] * 50 + ofRandom(200) - 100;
				ofDrawRectangle(currentX - xStep / 2, currentY - currentW / 2, xStep, currentW);
			}
			break;
		case 7:
			currentW = xStep;

			for (int j = 0; j < 10; ++j) {
				currentY = values[i] * 50 + ofRandom(200) - 100;
				currentY -= fmod(currentY, xStep);
				ofDrawRectangle(currentX - xStep / 2, currentY - currentW / 2, xStep, currentW);
			}
			break;
		case 8:
			currentW = xStep;

			for (int j = 0; j < 25; ++j) {
				currentY = values[i] * 50 + gen();
				currentY -= fmod(currentY, xStep);
				ofDrawRectangle(currentX - xStep / 2, currentY - currentW / 2, xStep, currentW);
			}
			break;
		default:
			ofLogNotice("boop");
		}
	}
	ofPopMatrix();
}

void Wave::assign(vector<float> _vals) {
	values.clear();
	values.resize(_vals.size());

	for (int i = 0; i < _vals.size(); ++i) {
		values[i] = _vals[i];
	}
}

Wave Wave::sum(vector<Wave*> waves) {
	Wave* wave = NULL;
	Wave newWave = Wave();
	int res = waves[0]->resolution;
	vector<float> newValues(res);
	newValues.assign(res, 0);

	for (int i = 0; i < waves.size(); ++i) {
		wave = waves[i];

		for (int j = 0; j < wave->resolution; ++j) {
			//ofLogNotice(j + " - " + wave->values.size());
			newValues[j] += wave->values[j];
		}
	}

	newWave.assign(newValues);

	return newWave;
}
