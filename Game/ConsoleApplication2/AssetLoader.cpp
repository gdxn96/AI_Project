#include "stdafx.h"
#include "AssetLoader.h"


AssetLoader * AssetLoader::instance = nullptr;
AssetLoader::AssetLoader()
{
}

void AssetLoader::addAssetToQueue(Asset* asset)
{
	this->assetQueue.push_back(asset);
}

void AssetLoader::loadAssetQueue()
{
	for (auto& asset : assetQueue)
	{
		loadAsset(asset);
	}
}

void AssetLoader::loadAsset(Asset* asset)
{
	SpriteData* spriteAsset = dynamic_cast<SpriteData*>(asset);

	m_currentAsset = asset->getKey();
	m_assetsLoaded++;

	if (spriteAsset)
	{
		addTextureToCache(spriteAsset->getKey(), spriteAsset->m_textureDir);
	}
}


void AssetLoader::loadTextures(string imgDataDir)
{
	string key, imgPath;
	ifstream myFile;
	myFile.open(imgDataDir);

	while (myFile >> key >> imgPath)
	{
		this->addAssetToQueue(new SpriteData(key, imgPath));
	}

}

AssetLoader * AssetLoader::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AssetLoader;
	}
	return instance;
}


void AssetLoader::addTextureToCache(string name, string _textureFilePath)
{
	sf::Texture * temp = new sf::Texture;

	if (!fileExists(_textureFilePath))
	{
		throw(LoadException("Texture " + name + " could not be loaded from " + _textureFilePath));
	}
	if (!temp->loadFromFile(_textureFilePath))
	{

		//printf("error, failed to load image: %f \n", _textureFilePath);
	}
	imageCache[name] = temp;
	std::cout << "Loading Texture : " << name << endl;
}


string AssetLoader::getLoadingAsset()
{
	return m_currentAsset;
}

int AssetLoader::getNumLoaded()
{
	return m_assetsLoaded;
}

int AssetLoader::getNumToLoad()
{
	return assetQueue.size();
}

void AssetLoader::addToImageCache(string name, string _textureFilePath)
{
	sf::Texture * temp = new sf::Texture;
	if (!temp->loadFromFile(_textureFilePath))
	{
		throw(LoadException("Texture " + name + " could not be loaded from " + _textureFilePath));
	}
	imageCache[name] = temp;
}



bool AssetLoader::exists(string key)
{
	auto it = imageCache.find(key);
	if (it != imageCache.end())
	{
		return true;
	}
	return false;
}

void AssetLoader::emptyMap()
{
	imageCache.clear();
}

sf::Texture * AssetLoader::findTextureByKey(string key)
{
	auto it = imageCache.find(key);
	if (it != imageCache.end())
	{
		return it->second;
	}
	else
	{
		cout << " key not in texture map : " << key << endl;
	}

}

AssetLoader::~AssetLoader()
{
}


