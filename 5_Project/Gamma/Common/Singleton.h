#pragma once
template<typename T>
class Singleton
{
public:
	static T* Instance();
};


template<typename T>
T* Singleton<T>::Instance()
{
	static T* instance = new T();
	return instance;
}