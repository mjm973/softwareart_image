#include "ofApp.h"
#include "../behaviors.h"

//--------------------------------------------------------------
void ofApp::setup() {
	spawner = Spawner(ofVec2f(0, -10));
	spawner.setPeriod(0.1)->setRate(1)->setSpawn(spawnRain);

	mainGui.setup("floop");
	mainGui.add(currentScene.setup("Current Scene", 0, 0, 6));
	mainGui.add(mainRate.setup("Main Rate", 1, 0, 16));
	mainGui.add(mainPeriod.setup("Main Period", 0.5, 0.1, 5));
	mainGui.add(mainLife.setup("Max Life", 2, 0, 30));
	mainGui.add(mainParam.setup("Main Param", ofVec4f(0, 0, 0, 0), ofVec4f(0, 0, 0, 0), ofVec4f(150, 150, 150, 150)));
	
	pRate = mainRate;
	pPeriod = mainPeriod;
	pLife = mainLife;
	pParam = mainParam;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!playback) {
		scene = currentScene;

		cRate = mainRate;
		cPeriod = mainPeriod;
		cLife = mainLife;
		cParam = mainParam;
	}

	if (scene != prevScene) {
		sceneChanged();
	}

	if (cRate != pRate
		|| cPeriod != pPeriod
		|| cLife != pLife
		|| cParam != pParam) {
		guiChanged();
	}

	spawner.update();

	switch (scene) {
	case Scene::seed:
	{
		break;
	}
	case Scene::roots:
	{
		break;
	}
	}

	prevScene = scene;
	pRate = cRate;
	pPeriod = cPeriod;
	pLife = cLife;
	pParam = cParam;
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (currentScene) {
	case Scene::seed:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	case Scene::roots:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();

		break;
	}
	case Scene::rain:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	case Scene::sprout:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	case Scene::sun:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	case Scene::flower:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	case Scene::wind:
	{
		ofBackground(255);

		ofPushMatrix();
		ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
		spawner.draw();
		ofPopMatrix();
		break;
	}
	}

	if (!playback) {
		mainGui.draw();
	}
}

//------------------------------------------------

void ofApp::guiChanged() {
	spawner.setRate(cRate)
		->setPeriod(cPeriod)
		->maxLife = cLife;
	spawner.param = cParam;
}

void ofApp::setScene() {
	float w = ofGetWidth()*0.5;
	float h = ofGetHeight()*0.5;

	switch (scene) {
	case Scene::seed:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnSeedRing)
			->setPos(ofVec2f(0, -h - 20))
			->setPosFunction(posSeed)
			->setVelFunction(NULL)
			->setAccFunction(NULL)
			->setDrawFunction(drawSeed);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::roots:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnRootSpawn)
			->setPos(ofVec2f(0, -h))
			->setVel(ofVec2f(0, 200))
			->setDrawFunction(drawRootSpawn);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::rain:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnRain)
			->setPos(ofVec2f(0, -h));
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::sprout:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnStalk)
			->setPos(ofVec2f(0, h))
			->setVel(ofVec2f(0, -50))
			->setDrawFunction(drawLeaf);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::sun:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnRay)
			->setDrawFunction(drawSun);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::flower:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnPetal);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	case Scene::wind:
	{
		spawner.setRate(cRate)
			->setPeriod(cPeriod)
			->setSpawn(spawnWindPetal);
		spawner.maxLife = cLife;
		spawner.param = cParam;
	}
		break;
	}
}

void ofApp::sceneChanged() {
	spawner.clear();

	switch (scene) {
	case Scene::seed:
	{
		mainRate = 1;
		mainPeriod = 0.5;
	}
	break;
	case Scene::roots:
	{
		mainRate = 1;
		mainPeriod = 0.1;
		mainLife = 3;
	}
	break;
	case Scene::rain:
	{
		mainRate = 1;
		mainPeriod = 0.2;
	}
	break;
	case Scene::sprout:
	{
		mainRate = 1;
		mainPeriod = 0.5;
		mainParam = ofVec4f(10, 20, 0, 0);
	}
		break;
	case Scene::sun:
	{
		mainRate = 5;
		mainPeriod = 0.3;
		mainParam = ofVec4f(20, 20, 0, 0);
	}
		break;
	case Scene::flower:
	{
		mainRate = 1;
		mainPeriod = 0.3;
		mainParam = ofVec4f(30, 0, 5, 0);
	}
	break;
	case Scene::wind:
	{
		mainRate = 3;
		mainPeriod = 0.45;

	}
	break;
	}

	setScene();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'a':
	case 'A':
		--scene;
		if (scene < 0) {
			scene = 0;
		}
		break;
	case 's':
	case 'S':
		playback = !playback;
		break;
	case 'd':
	case 'D':
		++scene;
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
	switch (button) {
	case 2:
		spawner.clear();
		guiChanged();
		setScene();
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
