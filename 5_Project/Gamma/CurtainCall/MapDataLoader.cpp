#include <fstream>
#include <vector>

#include "MapDataLoader.h"

MapDataLoader::MapDataLoader()
{
	mapDatas_.push_back(std::vector<Data>());
	mapDatas_.push_back(std::vector<Data>());
	mapDatas_.push_back(std::vector<Data>());

	std::ifstream fin("Map\\map01.txt");
	if (fin.fail())
	{
		return;
	}

	int id, triggerID, reactantID, index, linkedIndex;
	float x, y;
	while (fin >> id >>triggerID >> reactantID >> index >> linkedIndex >> x >> y)
	{
		mapDatas_[0].push_back(Data(id, triggerID, reactantID, index, linkedIndex, x, y));
	}

	fin.close();
}

std::vector<Data>& MapDataLoader::GetMapData(int mapNumber)
{
	if (mapNumber >= mapDatas_.size())
	{
		return mapDatas_[0];
	}

	return mapDatas_[mapNumber];
}
