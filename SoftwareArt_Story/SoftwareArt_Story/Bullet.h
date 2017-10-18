#pragma once

#include "ofMain.h"

class Bullet
{
protected:
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;

	ofVec2f(*posFunc)(Bullet* bul, float _time) = NULL;
	ofVec2f(*velFunc)(Bullet* bul, float _time) = NULL;
	ofVec2f(*accFunc)(Bullet* bul, float _time) = NULL;

	void(*drawFunc)(Bullet* bul) = NULL;

	bool checkBounds();
	bool dead = false;

	float lastTime = 0;
	float currentTime = 0;
	float deltaTime = 1./60.;

public:
	Bullet(ofVec2f pos = ofVec2f(), ofVec2f vel = ofVec2f(), ofVec2f acc = ofVec2f());

	~Bullet();

	float lifetime = 0;
	float maxLife = 0;

	bool paused = false;

	ofVec4f param = ofVec4f();

	ofVec2f getPos();
	ofVec2f getVel();

	virtual Bullet* setPos(ofVec2f newPos);
	virtual Bullet* setVel(ofVec2f newVel);

	virtual Bullet* setDrawFunction(void(*func)(Bullet* bul));
	virtual Bullet* setPosFunction(ofVec2f(*func)(Bullet* bul, float _time) = NULL);
	virtual Bullet* setVelFunction(ofVec2f(*func)(Bullet* bul, float _time) = NULL);
	virtual Bullet* setAccFunction(ofVec2f(*func)(Bullet* bul, float _time) = NULL);

	virtual void update();
	virtual void draw();

	virtual void clear();
	virtual void die();

	bool isDead();

	static float timestep;
};

