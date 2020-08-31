#include "Block.h"

Block::Block()
{
	
}
Block::~Block()
{

}

int Block::GetHP() const
{
	return mHP;
}
void Block::SetHP(int hp)
{
	mHP = hp;
}
