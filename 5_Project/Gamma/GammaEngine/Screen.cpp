#include "stdafx.h"
#include "Screen.h"
using namespace GammaEngine;
int Screen::width;
int Screen::height;

GammaEngine::Screen::Screen()
{
	RECT rect;
	GetWindowRect(NULL, &rect);
// 	width = GetSystemMetrics(SM_CXSCREEN);
// 	height= GetSystemMetrics(SM_CYSCREEN);
	width = 1920;
	height = 1080;
}

GammaEngine::Screen::Screen(int w, int h)
{
	width = w;
	height = h;
}

GammaEngine::Screen::~Screen()
{

}

void GammaEngine::Screen::SetSize(int w, int h)
{
	width = w;
	height = h;
}