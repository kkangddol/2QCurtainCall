#pragma once
class HighLightEffect : public Effect
{
public:
	vector3 color;
	vector3 position;

public:
	HighLightEffect();
	void SetColor(vector3);
	void SetPosition(vector3);

};
