#pragma once
#include <string>

class serializer
{
public:
	static void saveScene();
	static void saveScene(std::string filepath);
	static void openScene();
	static void openScene(std::string filepath);

private:
	static void save(std::string filepath);
	static void open(std::string filepath);
};
