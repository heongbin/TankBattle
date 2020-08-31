#include "GameObject.h"


GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

int GameObject::GetX() const
{
	return mX;
}
int GameObject::GetY() const
{
	return mY;
}
int GameObject::GetSize() const
{
	return mSize;
}
char* GameObject::GetImage() const
{
	return mpImage;
}
void GameObject::SetX(int x)
{
	mX = x;
}
void GameObject::SetY(int y)
{
	mY = y;
}
void GameObject::SetSize(int size)
{
	mSize = size;
}
void GameObject::SetImage(char* image)
{
	mpImage = image;
}