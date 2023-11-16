#pragma once

#include <string>

struct Level {

};

class LevelLoader
{
private:
	static LevelLoader* instance;
	std::string path;
	

	LevelLoader();

public:
	static LevelLoader* GetInstance() { return instance; }
	~LevelLoader();

	static void Initialize();

	Level GetLevelData();
	void LoadLevel(std::string path);
};