#pragma once

template<typename T>
class IDisposable {
public:
	virtual void Dispose() = 0;
};