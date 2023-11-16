#include "LevelLoader.hpp"

LevelLoader* LevelLoader::instance = nullptr;

LevelLoader::LevelLoader()
{}

LevelLoader::~LevelLoader() {
	delete instance;
}

void LevelLoader::Initialize() {
	if (instance != nullptr) return;
	instance = new LevelLoader();
}

Level LevelLoader::GetLevelData() {
	return Level();
}

void LevelLoader::LoadLevel(std::string path) {
}