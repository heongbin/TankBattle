#pragma once

#include "Singleton.h"

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();

	template <class A, class B>
	bool SquareCollisionCheck(A a, B b)
	{
		int x1 = a->GetX();
		int y1 = a->GetY();
		int size1 = a->GetSize();
		int x2 = b->GetX();
		int y2 = b->GetY();
		int size2 = b->GetSize();

		if (x1 < x2 + size2 &&
			y1 < y2 + size2 &&
			x1 + size1 > x2 &&
			y1 + size1 > y2)
		{
			return true;
		}

		return false;
	}

};

