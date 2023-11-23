#pragma once
#include <string>
#include "Renderer.h"
#include "Vector2D.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(GameObject* obj);
	~SpriteRenderer();

public:
	virtual void Render() override;

public:
	void LoadBitmapImage(std::wstring filename);
	void SetFlipX(bool);
	void SetFlipY(bool);
	Vector2D GetSize() const;
	void SetSize(Vector2D size);
	void SetSize(float x, float y);
	void SetOffset(Vector2D offset);
	void SetOffset(float x, float y);

private:
	std::wstring bitmap_;
	bool flipX_;
	bool flipY_;
	Vector2D size_;
	Vector2D offset_;
};
