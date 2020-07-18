#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
public:
	static T* getSingleton();
	void releaseSingleton();
};

template <typename T>
T* singletonBase<T>::singleton = 0;

template<typename T>
inline T * singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;

	return singleton;;
}

template<typename T>
inline void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
