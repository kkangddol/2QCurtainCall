#pragma once
#include "Renderer.h"

class UISpriteRenderer : public Renderer
{
public:
	UISpriteRenderer(GameObject* obj);
	~UISpriteRenderer();

public:
	virtual void Render() override;

public:
	void LoadBitmapImage(std::wstring filename);
	void SetFlipX(bool);
	void SetFlipY(bool);
	void SetSize(int width, int height);

private:
	std::wstring bitmap_;
	bool flipX_;
	bool flipY_;
	Vector2D size_;
	Vector2D offset_;
};
