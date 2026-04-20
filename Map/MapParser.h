#pragma once
#include "TileLayer.h"
#include "GameMap.h"

#include "..\tinyxml\tinyxml.h"

#include <map>
#include <string>

class MapParser
{
public:
	GameMap* Load(string mapName, string fileName);
	void Clean();

	inline static MapParser& GetInstance()
	{
		static MapParser MapParserInstance;
		return MapParserInstance;
	}

private:
	MapParser();
	GameMap* Parse(string mapId, string sourceFile);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesetList, int tileSize, int rowCount, int colCount);

	map<string, GameMap*> mMapDict;
};

