#pragma once
#include "Bullet.h"

class Spawner :
	public Bullet
{
	bool fire = false;
	float timer = 0;
	float period = -1;
	int rate = 0;

	void(*spawnFunc)(Spawner* spawn, float _t) = NULL;

	vector<Bullet*> children;

public:
	Spawner(ofVec2f pos = ofVec2f(), ofVec2f vel = ofVec2f(), ofVec2f acc = ofVec2f());
	~Spawner();
	
	Spawner* spawn(Bullet* b);

	int getRate();
	float getPeriod();

	Spawner* setPeriod(float _p);
	Spawner* setRate(int _r);
	Spawner* setSpawn(void(*func)(Spawner* spawn, float _t));

	void update();
	void draw();

	void clear();
};

