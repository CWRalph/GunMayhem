#pragma once
#include "SymbolDefines.h"
extern std::unordered_map<string, Texture2D> textures;

class Level
{
private:
	string Platform, BG;
	vector<Rectangle> platforms;
	vector<int> xPos;
public:
	Level() {};
	Level(string BGKey, string PlatformKey, const vector<int>& x): BG(BGKey), Platform(PlatformKey), xPos(x) {}
	Level(const Level& l)
	{
		Platform = l.Platform;
		BG = l.BG;
		platforms = l.platforms;
		xPos = l.xPos;
	}
	inline const short getPlatformCount() const { return (short)platforms.size(); }
	inline const vector<Rectangle>& getPlatforms() const
	{
		return platforms;
	}
	inline void addPlatform(Rectangle rec)
	{
		platforms.push_back(rec);
	}
	void Draw() const;
	inline const vector<int>& GetXPositions() const { return xPos; }

	~Level(){};

};

