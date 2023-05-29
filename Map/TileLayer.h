#pragma once
#include "Layer.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

struct TileSource
{
	int Height, Width;
	string Name, SourceFile;
};

struct Tileset
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileWidth, TileHeight, TileSize;
	string Name, Sourcefile;
	map<int, TileSource> TileSourceMap;
};

using TilesetList = vector<Tileset>;
using TileMap = vector < vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(string name, int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tileSetList);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return mTileMap; }

private:
	int mTileSize, mRowCount, mColCount;
	TileMap mTileMap;
	TilesetList mTileSets;
};

