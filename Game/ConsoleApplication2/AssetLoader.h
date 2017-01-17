#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "Asset.h"
#include <iostream>

using namespace std;


struct LoadException : public std::exception
{
	std::string s;
	LoadException(std::string ss) : s(ss) { printf(s.c_str()); }
	~LoadException() throw () {}
	const char* what() const throw() { return s.c_str(); }
};

inline bool fileExists(const std::string& name) {
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	else {
		f.close();
		return false;
	}
}

class AssetLoader
{
public:
	static AssetLoader * getInstance();
	~AssetLoader();
	bool exists(string key);
	void emptyMap();
	void addTextureToCache(string name, string _textureFilePath);
	sf::Texture * findTextureByKey(string key);

	void loadTextures(string imgDataDir);
	void addAssetToQueue(Asset* asset);
	void loadAssetQueue();
	void loadAsset(Asset* asset);


	string getLoadingAsset();
	int getNumLoaded();
	int getNumToLoad();
protected:
	void addToImageCache(string name, string _textureFilePath);
	AssetLoader();
	static AssetLoader * instance;
	map<string, sf::Texture *>  imageCache;

	vector<Asset*> assetQueue;

	int m_assetsLoaded;
	string m_currentAsset;
};

