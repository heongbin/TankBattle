#include "Player.h"

Player::Player()
{
	bIsDead = false;
}
Player::~Player()
{

}


int Player::GetDir() const
{
	return mDir;
}
int Player::GetHP() const
{
	return mHP;
}
int Player::GetDamage() const
{
	return mDamage;
}
bool Player::GetIsDead() const
{
	return bIsDead;
}


void Player::SetDir(int dir)
{
	mDir = dir;
}
void Player::SetHP(int hp)
{
	mHP = hp;
}
void Player::SetDamage(int damage)
{
	mDamage = damage;
}

void Player::Update()
{
	if (bIsDead)
	{
		mTimer.Update();
		if (mTimer.Timeout())
			Respawn();
	}
	
}

void Player::Death()
{
	if (!bIsDead)
	{
		mTimer.Init();
		mTimer.SetTimeout(4.0f);
		bIsDead = true;

		if (mX > 25)
			mX = 3;
		else
			mX = 44;

		if (mY > 15)
			mY = 3;
		else
			mY = 24;
	}
	
		
	
}
void Player::Respawn()
{
	bIsDead = false;
	mHP = 5;
	mDamage = 1;
	
	
}