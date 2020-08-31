#pragma once
#include "GameObject.h"

class Block : public GameObject
{
public:
	Block();
	~Block();

	int GetHP() const;
	void SetHP(int hp);

private:
	int mHP;
};

