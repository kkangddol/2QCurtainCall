#pragma once

using namespace GammaEngine;

class IngameUI : public GammaEngine::Component
{
public:
	enum class UIType
	{
		PAUSE,
		CLEAR
	};

	IngameUI(GameObject* obj);

	virtual void Start() override;
	virtual void OnDisable() override;
	virtual void OnEnable() override;

public:
	void StartClear(int score);
	void OnLeftInput();
	void OnRighttInput();
	void OnSelectInput();
	void SetSelector(GameObject* obj);
	void SetType(UIType type);
	void AddScore(GameObject* score);

private:
	UIType type_;
	int index_;
	int scoreValue_;
	GameObject* selector_;
	std::vector<GameObject*> scores_;
};

