#pragma once
#include <string>
#include <unordered_map>

class FileDataApplier
{
public:
	FileDataApplier(std::string path);
	void SetProperty(const std::string& propertyName, float& prop);
	void Apply();

private:
	std::unordered_map<std::string, float&> appliedProperties;
	std::string filepath;
};

class FileData
{
public:
	FileData(std::string path);
public:
	std::unordered_map<std::string, std::string> properties;
};