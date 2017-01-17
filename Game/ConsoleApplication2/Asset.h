#pragma once
#include <string>
#include <functional>

using namespace std;

struct Asset
{
public:
	Asset(string key) : m_key(key)
	{

	}

	virtual string getKey()
	{
		return m_key;
	}

protected:
	string m_key;

};



struct SpriteData : Asset
{
	SpriteData(string key, string textureDir) : Asset(key), m_textureDir(textureDir)
	{

	}

	string m_textureDir;
};


