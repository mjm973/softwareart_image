#pragma once

#include "behaviors.h"

#include "Bullet.h"
#include "Spawner.h"

// ~~~~~~ Bullet Behaviors ~~~~~~~
// Seed

void drawSeed(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());
	ofRotate(ofGetElapsedTimef() * 360);

	ofSetColor(87, 73, 7);
	ofDrawEllipse(0, 0, 20, 15);

	ofPopMatrix();
}

void drawSeedRing(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	float life = bul->lifetime;

	if (life <= 3) {
		float alpha = ofMap(bul->lifetime, 0., 3., 0, 255, true);

		ofSetColor(245, 206, 20, 255 - alpha);
		ofDrawCircle(0, 0, 5);
	}
	else {
		bul->die();
	}

	ofPopMatrix();
}


ofVec2f posSeed(Bullet* bul, float t) {
	ofVec2f old = bul->getPos();

	float y = ofLerp(old.y, 0, 0.01);

	return ofVec2f(old.x, y);
}

ofVec2f posSeedRing(Bullet* bul, float t) {
	ofVec2f old = bul->getPos();
	ofVec2f target = (bul->getVel()).getNormalized() * 300;

	float x = ofLerp(old.x, target.x, 0.01);
	float y = ofLerp(old.y, target.y, 0.01);

	return ofVec2f(x, y);
}


void spawnSeedRing(Spawner* spawn, float t) {
	ofVec2f pos, vel;

	float rate = spawn->getRate();
	float step = TWO_PI / rate;

	Bullet* next;

	float theta = t;

	for (int i = 0; i < rate; ++i, theta += step) {
		vel = ofVec2f(cos(theta), sin(theta));
		next = new Bullet(vel * 10, vel);

		next->setPosFunction(posSeedRing)->setDrawFunction(drawSeedRing);

		spawn->spawn(next);
	}
}

// Roots

void drawRootSpawn(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(74, 51, 5);
	ofDrawCircle(0, 0, 5);

	ofPopMatrix();
}

void drawRoot(Bullet* bul) {
	float size = ofMap(bul->lifetime, 0, 10, 5, 10, true);

	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(74, 51, 5);
	ofDrawCircle(0, 0, size);

	ofPopMatrix();
}


void spawnRootSpawn(Spawner* spawn, float t) {
	Bullet* root = new Bullet(spawn->getPos());
	root->setDrawFunction(drawRoot);
	spawn->spawn(root);

	float life = spawn->maxLife * 0.5;
	float rate = spawn->getRate();
	float period = spawn->getPeriod();

	if (spawn->lifetime >= spawn->maxLife) {
		ofVec2f vel;
		Spawner* next;

		if (life > 1) {
			for (int i = 0; i < 2; ++i) {
				vel = (spawn->getVel()).getRotatedRad(ofRandom(-PI / 3, PI / 3));

				next = new Spawner(spawn->getPos(), vel);
				next->setRate(rate)
					->setPeriod(period)
					->setSpawn(spawnRootSpawn)
					->setDrawFunction(drawRootSpawn);
				next->maxLife = life;

				spawn->spawn(next);
			}
		}
		spawn->paused = true;
	}
	else {
		float dart = ofRandomf();
		if (dart < 0.5 && life > 0.8) {
			ofVec2f vel = (spawn->getVel()).getRotatedRad(ofRandom(-PI / 3, PI / 3));

			Spawner* next = new Spawner(spawn->getPos(), vel);
			next->setRate(rate)
				->setPeriod(period)
				->setSpawn(spawnRootSpawn)
				->setDrawFunction(drawRootSpawn);
			next->maxLife = life;

			spawn->spawn(next);
		}
		else if (dart > 0.5) {
			ofVec2f vel = (spawn->getVel()).getRotatedRad(ofRandom(-PI / 3, PI / 3));

			spawn->setVel(vel);
		}
	}
}

// Rain

void drawRaindrop(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(100, 100, 255);
	ofVec2f tail = -(bul->getVel()).getNormalized();
	float rad = 5;

	for (int i = 0; i < 4; ++i) {
		ofDrawCircle(tail * 10 * i, rad);

		rad *= 0.5;
	}

	ofPopMatrix();
}


void spawnRain(Spawner* spawn, float t) {
	ofVec2f vel = ofVec2f(ofRandom(-50, 50), 500);
	ofVec2f pos = ofVec2f();
	float w = ofGetWidth()*0.5;
	float h = ofGetHeight()*0.5;

	Bullet* next;
	for (int i = 0; i < spawn->getRate(); ++i) {
		pos = ofVec2f(ofRandom(-w, w), -h);
		next = new Bullet(pos, vel);
		next->setDrawFunction(drawRaindrop);

		spawn->spawn(next);
	}
}

// Sprout

void drawStalk(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(0, 255, 0);

	ofBeginShape();
	ofVertex(-10, -10);
	ofVertex(10, -10);
	ofVertex(5, 0);
	ofVertex(10, 10);
	ofVertex(-10, 10);
	ofVertex(-5, 0);
	ofEndShape(true);

	ofPopMatrix();
}

void drawLeaf(Bullet* bul) {
	float angle = bul->getVel().angle(ofVec2f(1, 0));
	float scale = ofMap(bul->lifetime, 0, bul->maxLife, 1, 2.5, true);

	ofPushMatrix();
	ofTranslate(bul->getPos());
	ofRotateZ(-angle);
	ofScale(ofVec3f(scale, scale, scale));

	ofSetColor(50, 255, 50);
	ofBeginShape();
	ofVertex(0, 0);
	ofVertex(20, 10);
	ofVertex(40, 0);
	ofVertex(20, -10);
	ofEndShape(true);

	ofPopMatrix();
}


ofVec2f posLeaf(Bullet* bul, float f) {
	ofVec2f target = bul->param + (bul->getVel().getNormalized()) * bul->param.z*5;
	float x = ofMap(bul->lifetime, 0, bul->maxLife, bul->getPos().x, target.x);
	float y = ofMap(bul->lifetime, 0, bul->maxLife, bul->getPos().y, target.y);

	return ofVec2f(x, y);
}

void spawnStalk(Spawner* spawn, float t) {
	Bullet* stalk, *leaf;

	stalk = new Bullet(spawn->getPos());
	stalk->setDrawFunction(drawStalk);
	spawn->spawn(stalk);

	if (ofRandomf() < 0.2) {
		leaf = new Bullet(spawn->getPos());
		leaf->setVel(ofVec2f(1, -1))
			->setPosFunction(posLeaf)
			->setDrawFunction(drawLeaf);
		leaf->maxLife = spawn->param.x;
		leaf->param = spawn->getPos();
		leaf->param.z = spawn->param.y;

		spawn->spawn(leaf);
	}

	if (ofRandomf() < 0.2) {
		leaf = new Bullet(spawn->getPos());
		leaf->setVel(ofVec2f(-1, -1))
			->setPosFunction(posLeaf)
			->setDrawFunction(drawLeaf);
		leaf->maxLife = spawn->param.x;
		leaf->param = spawn->getPos();
		leaf->param.z = spawn->param.y;

		spawn->spawn(leaf);
	}
}

// Sun

void drawSun(Bullet* bul) {
	float scale = ofMap(sin(bul->lifetime), -1, 1, 1, 2);

	ofPushMatrix();
	ofTranslate(bul->getPos());
	ofScale(ofVec3f(scale, scale, scale));

	ofSetColor(255, 255, 0);
	ofDrawCircle(0, 0, 50);

	ofPopMatrix();
}

void drawRay(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());
	ofRotate(ofRadToDeg(bul->lifetime));
	ofScale(ofVec3f(20, 20, 20));

	ofDrawTriangle(ofVec2f(1, 0), ofVec2f(cos(TWO_PI / 3), sin(TWO_PI / 3)), ofVec2f(cos(2 * TWO_PI / 3), sin(2 * TWO_PI / 3)));

	ofPopMatrix();
}


void spawnRay(Spawner* spawn, float t) {
	// Bullets toward point on circle

	Bullet* ray;
	ofVec2f nextPos, nextAim, nextVel;
	float theta = 0, thetaStep = TWO_PI / spawn->getRate();
	float base = spawn->param.x;
	float focal = spawn->param.y;

	for (int i = 0; i < spawn->getRate(); ++i, theta += thetaStep) {
		nextPos = ofVec2f(-sin(theta), cos(theta)) * base;
		nextAim = ofVec2f(cos(theta), sin(theta)) * focal;
		nextVel = (nextAim - nextPos).getNormalized() * 150;

		ray = new Bullet(nextPos, nextVel);
		ray->setDrawFunction(drawRay);

		spawn->spawn(ray);

		nextPos *= -1;
		nextVel = (nextAim - nextPos).getNormalized() * 150;

		ray = new Bullet(nextPos, nextVel);
		ray->setDrawFunction(drawRay);

		spawn->spawn(ray);
	}
}

// Flower

void drawFlower(Bullet* bul) {

}
// Shrink with time?
void drawPetal(Bullet* bul) {
	float scale = ofMap(bul->lifetime, 0, bul->maxLife, 10, 1, true);

	ofPushMatrix();
	ofTranslate(bul->getPos());
	ofScale(ofVec3f(scale, scale, scale));

	ofSetColor(255, 200, 200);

	//ofBeginShape();
	//ofBezierVertex(0, 0, 1.5, 1, 3, 0);
	//ofBezierVertex(3, 0, 1.5, -1, 0, 0);
	//ofEndShape(true);

	ofDrawCircle(0, 0, 5);

	ofPopMatrix();
}


ofVec2f velPetal(Bullet* bul, float t) {
	ofVec2f dir = bul->getVel().getNormalized();
	float l = bul->lifetime;
	float mag = 50 / sqrt(l + 1);//1+sqrt(l*l*l);

	return dir*mag;// *mag * 500;
}


void spawnPetal(Spawner* spawn, float t) {
	int n = int(spawn->param.x);
	float theta = spawn->param.y;
	float thetaStep = TWO_PI / spawn->getRate(); //fib(n) / fib(n + 2);

	Bullet* next;
	ofVec2f nPos, nVel;

	for (int i = 0; i < spawn->getRate(); ++i, theta += thetaStep) {
		nPos = ofVec2f(cos(theta), sin(theta)) * 20;
		nVel = nPos;

		next = new Bullet(nPos, nVel);
		next->setDrawFunction(drawPetal)
			->setVelFunction(velPetal)
			->maxLife = spawn->param.z;

		spawn->spawn(next);
	}
	spawn->param.y += (fib(n + 2) / fib(n));
}

// Wind

void drawWind(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(0, 255, 255);
	ofDrawCircle(0, 0, 5);

	ofPopMatrix();
}

void drawWindPetal(Bullet* bul) {
	ofPushMatrix();
	ofTranslate(bul->getPos());

	ofSetColor(255, 200, 200);
	ofDrawCircle(0, 0, 10);

	ofPopMatrix();
}

ofVec2f accWindPetal(Bullet* bul, float t) {
	return ofVec2f(0, ofSignedNoise(bul->param.x + t)) * 300;
}

void spawnWindPetal(Spawner* spawn, float t) {
	float dart = ofRandom(0, 1);
	float w = ofGetWidth()*0.5;
	float h = ofGetHeight()*0.5;

	Bullet* next;
	ofVec2f pos, vel;

	if (dart < 0.05) {
		pos = ofVec2f(-w, ofRandom(-h, h));
		vel = ofVec2f(250, 0);

		next = new Bullet(pos, vel);
		next->setAccFunction(accWindPetal)
			->setDrawFunction(drawWindPetal)
			->param.x = ofRandom(10);

		spawn->spawn(next);
	}

	for (int i = 0; i < spawn->getRate(); ++i) {
		pos = ofVec2f(-w, ofRandom(-h, h));
		vel = ofVec2f(500, 0);

		next = new Bullet(pos, vel);
		next->setDrawFunction(drawWind);

		spawn->spawn(next);
	}
}

// Util

float fib(int n) {
	float cur = 1;
	float last = 1;
	float temp = cur;

	if (n < 2) {
		return 1;
	}

	for (int i = 1; i < n; ++i) {
		temp += last;
		last = cur;
		cur = temp;
	}

	return cur;
}
