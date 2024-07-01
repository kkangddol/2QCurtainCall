#include "stdafx.h"
#include "Render.h"
#include "Direct2DModule.h"

#include <numeric>
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"

using namespace GammaEngine;
RenderModule* GammaEngine::GraphicSystem::render = nullptr;

GammaEngine::GraphicSystem::GraphicSystem()
{
	renderComponentList = new std::vector<Renderer*>();
}

GammaEngine::GraphicSystem::~GraphicSystem()
{
	
}

void GammaEngine::GraphicSystem::Initialize(HWND hWnd)
{
	Screen* screen = Screen::Instance();
// 	std::string path = "..//x64//Debug//Direct2DModule.dll";
// 	HMODULE hDll = ::LoadLibraryA(path.c_str());

//  	typedef RenderModule* (*DLLRenderModule)();
// 	DLLRenderModule renderFunc = (DLLRenderModule)::GetProcAddress(hDll, "CreateRenderModule");
// 	render = renderFunc();
	render = new Direct2DModule();
	render->Initialize(hWnd);
}

void GammaEngine::GraphicSystem::Release()
{
	render->Release();
}

void GammaEngine::GraphicSystem::Frame()
{
	render->BeginDraw();
	
	std::vector<Renderer*> renderList = *renderComponentList;
	std::sort(renderList.begin(), renderList.end(), [](Renderer* a, Renderer* b) {
		return a->order < b->order;
	});

	std::list<Particle*> particleList;
	for (auto& particleSystem : *(ParticleManager::Instance()->GetSystems()))
	{
		for (auto& emitter : *(particleSystem->GetEmitters()))
		{
			particleList.insert(particleList.end(), emitter->GetRunningParticles()->begin(), emitter->GetRunningParticles()->end());
		}
	}

	particleList.sort([](Particle* a, Particle* b) {
		return a->GetOrder() < b->GetOrder();
		});
	
// 	std::sort(particleList.begin(), particleList.end(), [](Particle* a, Particle* b) {
// 		return a->GetOrder() < b->GetOrder();
// 		});

	auto renderIter = renderList.begin();
	auto particleIter = particleList.begin();

	while (renderIter != renderList.end() && particleIter != particleList.end())
	{
		if ((*renderIter)->order <= (*particleIter)->GetOrder())
		{
			if ((*renderIter)->isEnabled && (*renderIter)->gameObject->isEnabled)
			{
				(*renderIter)->Render();
			}
			++renderIter;
		}
		else
		{
			(*particleIter)->Render();
			++particleIter;
		}
	}

	while (renderIter != renderList.end())
	{
		if ((*renderIter)->isEnabled && (*renderIter)->gameObject->isEnabled)
		{
			(*renderIter)->Render();
		}
		++renderIter;
	}

	while (particleIter != particleList.end())
	{
		(*particleIter)->Render();
		++particleIter;
	}

	Debug::Render();
	render->EndDraw();
}

void GammaEngine::GraphicSystem::Resize(int width, int height)
{
	render->Resize(width, height);
}

void GammaEngine::GraphicSystem::DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material)
{
	render->DrawRectangle(size, matrix, material);
}

void GammaEngine::GraphicSystem::DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material)
{
	render->DrawEllipse(size, matrix, material);
}

void GammaEngine::GraphicSystem::DrawLine(vector2 start, vector2 end,Matrix3x3 matrix, Material* material)
{
	render->DrawLine(start, end, matrix, material);
}

void GammaEngine::GraphicSystem::DrawTextBox(vector2 size, Matrix3x3 matrix, std::wstring text, std::wstring fontFamily, Material* material)
{
	render->DrawTextBox(size, matrix,text, fontFamily, material);
}

void GammaEngine::GraphicSystem::DrawBitmap(std::wstring bitmap, vector2 size, Matrix3x3 matrix, Material* material, std::vector<IEffect*>* appliedEffects)
{
	render->DrawBitmap(bitmap, size, matrix, material, appliedEffects);
}

void GammaEngine::GraphicSystem::DrawBitmap(std::wstring bitmap, vector2 originalSize, vector2 size, vector2 offset, Matrix3x3 matrix, Material* material,std::vector<IEffect*>* appliedEffects)
{
	render->DrawBitmap(bitmap, originalSize, size, offset, matrix, material, appliedEffects);
}

void GammaEngine::GraphicSystem::DrawPolygon(std::wstring name, Matrix3x3 matrix, Material* material)
{
	render->DrawPolygon(name, matrix, material);
}

wstring GammaEngine::GraphicSystem::LoadBitmapImage(std::wstring filename)
{
	return render->LoadBitmapImage(filename);
}

vector2 GammaEngine::GraphicSystem::GetBitmapSize(std::wstring bitmap)
{
	return render->GetBitmapSize(bitmap);
}

std::wstring GammaEngine::GraphicSystem::MakePolygon(std::wstring name, std::vector<vector2> points)
{
	return render->MakePolygon(name, points);
}