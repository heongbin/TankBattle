#pragma once
class GameObject
{

public:
	GameObject();
	~GameObject();

	int GetX() const;
	int GetY() const;
	int GetSize() const;
	char* GetImage() const;

	void SetX(int x);
	void SetY(int y);
	void SetSize(int size);
	void SetImage(char* image);

protected:
	int	mX;
	int	mY;
	int mSize;
	char* mpImage;

};

