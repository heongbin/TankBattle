#pragma once
#include "GameObject.h"
class Item :
	public GameObject
{
public:
	Item();
	~Item();

	int GetKind() const;

	void SetKind(int kind);


private:
	int mKind;
};

