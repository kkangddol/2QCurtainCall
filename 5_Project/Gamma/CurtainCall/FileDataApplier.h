#pragma once
#include <string>
#include <unordered_map>

class FileData
{
public:
	FileData(std::string path);
public:
	std::unordered_map<std::string, std::string> properties;
};

class Property
{
public:
	Property(float& data) :data_(data) {}
	void SetValue(float data)
	{
		data_ = data;
	}

private:
	float& data_;
};

class FileDataApplier
{
public:
	FileDataApplier(std::string path);
	void SetProperty(const std::string& propertyName, float& prop);
	void Apply();

private:
	std::unordered_map<std::string, Property*> appliedProperties;
	std::string filepath;
};


