#pragma once
#include "TerrainSegment.h"

class Terrain
{
public:
	static std::vector<TerrainSegment*> GenerateTerrain(int minY, int maxY, Vector2D levelSize);
private:
	static std::vector<int> calculateYValues(float minY, float maxY, float displace, float roughness);
	static bool valid(int value, int max, int min);
};
