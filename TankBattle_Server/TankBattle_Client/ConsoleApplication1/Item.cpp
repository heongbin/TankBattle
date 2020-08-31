#include "Item.h"


Item::Item()
{

}
Item::~Item()
{

}

int Item::GetKind() const
{
	return mKind;
}

void Item::SetKind(int kind)
{
	mKind = kind;
}