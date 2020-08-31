#pragma once
#include "GameObject.h"
#include "Timer.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	
	
	int GetDir() const;
	int GetHP() const;
	int GetDamage() const;
	bool GetIsDead() const;

	void SetDir(int dir);
	void SetHP(int hp);
	void SetDamage(int damage);


	void Update();
	void Death();
	void Respawn();

private:
	int mDir;
	int mHP;
	int mDamage;
	bool bIsDead;

	Timer mTimer;
};

