#pragma once
#include <list>
#include <mutex>

template<class T>
class ObjectPool
{
public:
	ObjectPool(int size = 10) {
		mMaxSize = size;
		for (int i = 0; i < mMaxSize; ++i) {
			T* newObject = new T();
			mObjects.push_back(newObject);
		}
	}
	~ObjectPool()
	{
		while (!mObjects.empty()) {
			mObjects.clear();
		}
		mMaxSize = 0;
		}

	T* PopObject()
	{
		if (!mObjects.empty())
		{
			T* retVal = mObjects.front();
			mObjects.pop_back();
			return retVal;
		}
		else
			return nullptr;
	}

	void ReturnObject(T* object)
	{
		mObjects.push_back(object);
	}



private:
	std::list<T*> mObjects;
	int mMaxSize; 
};
