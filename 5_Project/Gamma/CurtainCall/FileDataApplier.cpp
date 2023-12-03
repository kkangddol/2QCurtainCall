#include "FileDataApplier.h"
#include <fstream>
#include <sstream>


FileDataApplier::FileDataApplier(std::string path)
{
	filepath = path;
}

void FileDataApplier::SetProperty(const std::string& propertyName, float& prop)
{
	appliedProperties.insert({ propertyName, prop });
}

void FileDataApplier::Apply()
{
	FileData data = FileData(filepath);
	for (auto element : data.properties)
	{
		appliedProperties[element.first] = std::stof(element.second);
	}
}

FileData::FileData(std::string path)
{
	std::ifstream file(path.data());
	if(file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::vector<std::string> tokens;
			std::stringstream ss(line);
			std::string temp;
			while (getline(ss, temp, '=')) {
				tokens.push_back(temp);
			}
			properties.insert({ tokens[0],tokens[1] });
		}
	}
}
