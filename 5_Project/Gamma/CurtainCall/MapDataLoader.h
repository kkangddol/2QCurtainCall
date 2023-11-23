#pragma once

struct Data
{
	Data(int id,int tID, int rID, int i, int li, float X, float Y)
		: objectID(id),
		triggerID(tID),
		reactantID(rID),
		index(i),
		linkedIndex(li),
		x(X), y(Y)
	{

	}

	int objectID;
	int triggerID;
	int reactantID;
	int index;
	int linkedIndex;
	float x;
	float y;
};

class MapDataLoader
{
public:
	enum class eObject
	{
		BOX,
		LADDER,
		LEFTPLATFORM,
		RIGHTPLATFORM,
		WATERTANK,
		ARCH,
		ELEVATOR,
		CONTROL,
		MUSIC,
		WHEEL,
		SCAFFOLDING,
		LEVER,
		CYCLE,
		GONDOLA
	};

public:
	MapDataLoader();
	std::vector<Data>& GetMapData(int mapNumber);

private:
	std::vector<std::vector<Data>> mapDatas_;
};

