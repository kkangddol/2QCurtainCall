#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

#include <queue>

namespace GammaEngine
{
	template <typename T>
	class GammaEngineAPI ObjectPool
	{
	public:
		ObjectPool()
			:ObjectPool(0)
		{
			pool = new std::queue<T*>();
		}
		ObjectPool(size_t poolSize)
		{
			pool = new std::queue<T*>();
			for (size_t i = 0; i < poolSize; ++i)
			{
				pool.push(new T());
			}
		}

	public:
		T& GetObj()
		{
			if (pool.empty())
			{
				pool.push(new T());
			}

			T& temp = *(pool.front());
			pool.pop();
			return temp;
		}
		void ReturnObj(T& obj)
		{
			pool.push(&obj);
		}

	private:
		std::queue<T*>* pool;
	};
}
