#pragma once
#include "GameObject.h"
#include "Timer.h"

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	void Move();

	int GetDir() const;
	int GetDamage() const;

	void SetDir(int dir);
	void SetDamage(int damage);
	

private:
	
	int mDir;
	int mDamage;
	Timer mTimer;
};

