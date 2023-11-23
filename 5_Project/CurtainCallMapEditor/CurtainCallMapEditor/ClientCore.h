#pragma once
#include <string>

class ClientCore
{
public:
	void Initialize(const int screenWidth, const int screenHeight);
private:
	int screenWidth_;
	int screenHeight_;
};

