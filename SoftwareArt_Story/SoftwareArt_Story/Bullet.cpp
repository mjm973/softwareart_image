#include "Bullet.h"

Bullet::Bullet(ofVec2f _pos, ofVec2f _vel, ofVec2f _acc) {
	pos = _pos;
	vel = _vel;
	acc = _acc;

	lastTime = ofGetElapsedTimef();
}

Bullet::~Bullet()
{
}

bool Bullet::checkBounds() {
	float w = ofGetWidth()*0.5;
	float h = ofGetHeight()*0.5;
	float margin = 100;

	float xMax = w + margin;
	float yMax = h + margin;

	return (pos.x > xMax
		|| pos.x < -xMax
		|| pos.y > yMax
		|| pos.y < -yMax);
}

ofVec2f Bullet::getPos() {
	return pos;
}

ofVec2f Bullet::getVel() {
	return vel;
}

Bullet* Bullet::setPos(ofVec2f newPos) {
	pos = newPos;
	return this;
}

Bullet* Bullet::setVel(ofVec2f newVel) {
	vel = newVel;
	return this;
}

Bullet* Bullet::setDrawFunction(void(*func)(Bullet* bul)) {
	drawFunc = func;
	return this;
}

Bullet* Bullet::setPosFunction(ofVec2f(*func)(Bullet* bul, float _time)) {
	posFunc = func;
	return this;
}

Bullet* Bullet::setVelFunction(ofVec2f(*func)(Bullet* bul, float _time)) {
	velFunc = func;
	return this;
}

Bullet* Bullet::setAccFunction(ofVec2f(*func)(Bullet* bul, float _time)) {
	accFunc = func;
	return this;
}

void Bullet::update() {
	if (dead) {
		return;
	}

	if (checkBounds()) {
		die();
		return;
	}

	deltaTime = ofGetElapsedTimef() - lastTime;
	lastTime = ofGetElapsedTimef();

	//ofLogNotice(ofToString(ofGetLastFrameTime() - deltaTime));

	if (accFunc) {
		acc = accFunc(this, ofGetElapsedTimef());
	}
	else if (velFunc) {
		vel = velFunc(this, ofGetElapsedTimef());
	}
	else if (posFunc) {
		pos = posFunc(this, ofGetElapsedTimef());
	}

	if (!velFunc) {
		vel += acc*deltaTime;
	}


	if (!posFunc) {
		pos += vel*deltaTime;
	}


	acc *= 0;

	lifetime += deltaTime;
}

void Bullet::draw() {
	if (dead) {
		return;
	}

	if (drawFunc) {
		drawFunc(this);
	}
	//else {
	//	ofPushMatrix();
	//	ofTranslate(pos);
	//	ofSetColor(0);
	//	ofDrawCircle(ofVec2f(), 20);
	//	ofPopMatrix();
	//}
}

void Bullet::clear() {
	posFunc = NULL;
	velFunc = NULL;
	accFunc = NULL;
	drawFunc = NULL;

	pos = ofVec2f();
	vel = ofVec2f();
	acc = ofVec2f();
	param = ofVec4f();

	lifetime = 0;
	maxLife = 0;
	dead = false;
	paused = false;
}

void Bullet::die() {
	dead = true;
}

bool Bullet::isDead() {
	return dead;
}

float Bullet::timestep = float(1) / float(60);
