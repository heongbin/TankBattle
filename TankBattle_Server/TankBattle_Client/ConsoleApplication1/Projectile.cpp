#include "Projectile.h"

Projectile::Projectile()
{
	mTimer.SetTimeout(0.05f);
}


Projectile::~Projectile()
{
	
}


int Projectile::GetDir() const
{
	return mDir;
}

int Projectile::GetDamage() const
{
	return mDamage;
}

void Projectile::SetDir(int dir)
{
	mDir = dir;
}

void Projectile::SetDamage(int damage)
{
	mDamage = damage;
}


void Projectile::Move()
{
	mTimer.Update();
	if (mTimer.Timeout())
	{
		switch (mDir)
		{
		case 1:
			mY--;
			break;
		case 2:
			mY++;
			break;
		case 3:
			mX--;
			break;
		case 4:
			mX++;
			break;
		default:
			break;
		}
	}
	
}
