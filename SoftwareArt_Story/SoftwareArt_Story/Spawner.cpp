#include "Spawner.h"



Spawner::Spawner(ofVec2f _pos, ofVec2f _vel, ofVec2f _acc)
	: Bullet(_pos, _vel, _acc)
{

}


Spawner::~Spawner()
{
}

Spawner* Spawner::spawn(Bullet* b) {
	children.push_back(b);
	return this;
}

int Spawner::getRate() {
	return rate;
}

float Spawner::getPeriod() {
	return period;
}

Spawner* Spawner::setPeriod(float _p) {
	period = _p;
	return this;
}

Spawner* Spawner::setRate(int _r) {
	rate = _r;
	return this;
}

Spawner* Spawner::setSpawn(void(*func)(Spawner* spawn, float _t)) {
	spawnFunc = func;
	return this;
}

void Spawner::update() {
	if (!dead && !paused) {
		Bullet::update();
		fire = false;
		if (timer >= period && period > 0) {
			timer = 0;
			fire = true;
		}

		if (spawnFunc && fire) {
			spawnFunc(this, ofGetElapsedTimef());
		}
	}

	if (children.size() > 0) {
		Bullet* b;
		for (int i = children.size()-1; i >= 0; --i) {
			b = children[i];
			
			if (b->isDead()) {
				//children.erase(children.begin() + i);
				//delete b;
			}
			else {
				b->update();
			}
		}
	}

	timer += ofGetLastFrameTime();
}

void Spawner::draw() {
	if (!dead && !paused) {
		Bullet::draw();
	}

	if (children.size() > 0) {
		for each (Bullet* b in children) {
			b->draw();
		}
	}
}

void Spawner::clear() {
	Bullet::clear();

	int len = children.size();
	Bullet* cur;

	for (int i = len - 1; i >= 0; --i) {
		cur = children[i];
		delete cur;
	}

	children.clear();
}
