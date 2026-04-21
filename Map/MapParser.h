#pragma once
#include "TileLayer.h"
#include "GameMap.h"

#include "..\tinyxml\tinyxml.h"

#include <map>
#include <string>

class MapParser
{
public:
	unique_ptr<GameMap> Load(string mapName, string fileName);
	void Clean();

	inline static MapParser& GetInstance()
	{
		static MapParser MapParserInstance;
		return MapParserInstance;
	}

private:
	MapParser();
	unique_ptr<GameMap> Parse(string mapId, string sourceFile);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	unique_ptr<TileLayer> ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesetList, int tileSize, int rowCount, int colCount);

	map<string, GameMap*> mMapDict;
};

