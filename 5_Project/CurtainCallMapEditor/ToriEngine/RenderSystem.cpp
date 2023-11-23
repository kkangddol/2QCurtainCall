#include <algorithm>
#include "ToriD2D.h"
#include "Debug.h"
#include "Scene.h"
#include "Renderer.h"

#include "Matrix.h"
#include "RenderSystem.h"

ToriD2D* RenderSystem::graphicModule_ = nullptr;

RenderSystem::RenderSystem()
{

}

void RenderSystem::Initialize(const HWND& hWnd)
{
	graphicModule_ = &ToriD2D::Instance();
	graphicModule_->Initialize(hWnd);
	renderList_.clear();
}

void RenderSystem::Finalize()
{
// 	for (auto& vec : renderList_)
// 	{
// 		for (auto renderer : vec.second)
// 		{
// 			delete renderer;
// 		}
// 	}
}

void RenderSystem::Render(Scene* currentScene, Scene* UIScene)
{
	std::wstring renderCount;
	renderCount.append(L"renderCount : ");
	renderCount.append(std::to_wstring(renderList_[currentScene].size()));
	Debug::DrawTextToScreen(renderCount, Vector2D(400, 200), Vector2D(500, 0));

	graphicModule_->BeginDraw();
	RenderScene(currentScene);
	RenderScene(UIScene);
	Debug::BruteRender();
	Debug::Render();
	graphicModule_->EndDraw();
}

void RenderSystem::RenderScene(Scene* scene)
{
	std::vector<Renderer*>& renderList = renderList_.at(scene);
	std::sort(renderList.begin(), renderList.end(), [](Renderer* a, Renderer* b) {
		return a->GetOrder() < b->GetOrder();
		});

	for (auto render : renderList_[scene])
	{
		render->Render();
	}
}

void RenderSystem::SetBrushColor(float r, float g, float b, float a)
{
	graphicModule_->SetBrushColor(r, g, b, a);
}

void RenderSystem::DrawRect(Vector2D size, Matrix3x3 matrix)
{
	graphicModule_->DrawRect(size, matrix);
}

void RenderSystem::DrawCircle(float centerX, float centerY, float radius)
{
	graphicModule_->DrawCircle(centerX, centerY, radius);
}

void RenderSystem::DrawText2D(std::wstring str, float sizeX, float sizeY, Matrix3x3 matrix)
{
	graphicModule_->DrawText2D(str, sizeX, sizeY, matrix);
}

void RenderSystem::DrawText2D(const char* str, float left, float top, float r, float g, float b, float a)
{
	graphicModule_->DrawText2D(str, left, top, r, g, b, a);
}

void RenderSystem::DrawLine(float startX, float startY, float endX, float endY)
{
	graphicModule_->DrawLine(startX, startY, endX, endY);
}

void RenderSystem::DrawBitmap(std::wstring bitmap, Vector2D size, Matrix3x3 matrix)
{
	graphicModule_->DrawBitmap(bitmap, size, matrix);
}

void RenderSystem::DrawBitmap(std::wstring bitmap, Vector2D originalSize, Vector2D size, Vector2D offset, Matrix3x3 matrix)
{
	graphicModule_->DrawBitmap(bitmap, originalSize, size, offset, matrix);
}

std::wstring RenderSystem::LoadBitmapImage(std::wstring fileName)
{
	return graphicModule_->LoadBitmapImage(fileName);
}

Vector2D RenderSystem::GetBitmapSize(std::wstring fileName)
{
	return graphicModule_->GetBitmapSize(fileName);
}

ToriD2D* RenderSystem::GetGraphicModule()
{
	return graphicModule_;
}

void RenderSystem::AddList(Scene* nowScene, Renderer* const val)
{
	renderList_[nowScene].push_back(val);
}

void RenderSystem::RemoveList(Scene* nowScene, Renderer* const val)
{
	renderList_[nowScene].erase(remove(renderList_[nowScene].begin(), renderList_[nowScene].end(), val),renderList_[nowScene].end());
}

void RenderSystem::Resize(int width, int height)
{
	graphicModule_->Resize(width, height);
}

