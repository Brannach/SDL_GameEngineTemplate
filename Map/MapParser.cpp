#include "MapParser.h"

#include <string>

using namespace std;

GameMap* MapParser::Load(string mapName, string fileName)
{
	return Parse(mapName, fileName);
}

void MapParser::Clean()
{
	map<string, GameMap*>::iterator it;
	for (it = mMapDict.begin(); it != mMapDict.end(); it++)
		it->second = nullptr;
	mMapDict.clear();
}

MapParser::MapParser()
{
}

GameMap* MapParser::Parse(string mapId, string sourceFile)
{
	TiXmlDocument xmlDoc;
	xmlDoc.LoadFile(sourceFile);
	if (xmlDoc.Error())
	{
		cout << "Error opening map file: " << sourceFile << endl;
		return nullptr;
	}
	TiXmlElement* root = xmlDoc.RootElement();
	int rowCount, colCount, tileSize;
	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);
	
	TilesetList tilesetList;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("tileset"))
		{
			tilesetList.push_back(ParseTileset(e));
		}
	}

	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("layer"))
		{
			TileLayer* tileLayer = ParseTileLayer(e, tilesetList, tileSize, rowCount, colCount);
			gameMap->mColCount = colCount;
			gameMap->mRowCount = rowCount;
			gameMap->mTileSize = tileSize;
			gameMap->mMapLayers.push_back(unique_ptr<Layer>(move(tileLayer)));
		}
	}
	mMapDict[mapId] = gameMap;
	return mMapDict[mapId];
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	if (tileset.ColCount != 0)
		tileset.RowCount = tileset.TileCount / tileset.ColCount;
	else tileset.RowCount = 0;

	xmlTileset->Attribute("tilewidth", &tileset.TileWidth);
	xmlTileset->Attribute("tileheight", &tileset.TileHeight);

	TiXmlElement* element = xmlTileset->FirstChildElement();
	if (element->Value() == string("image") && element->Attribute("source") != nullptr)
	{
		tileset.Sourcefile = element->Attribute("source");
	}
	else
	{
		if (element->Value() == string("grid"))
		{
			element->Attribute("width", &tileset.ColCount);
			element->Attribute("height", &tileset.RowCount);
			tileset.TileCount = tileset.ColCount * tileset.RowCount;
			for (TiXmlElement* nextEle = element->NextSiblingElement(); nextEle != nullptr; nextEle = nextEle->NextSiblingElement())
			{
				if (nextEle->Value() == string("tile"))
				{
					int tileId;
					nextEle->Attribute("id", &tileId);
					TiXmlElement* child = nextEle->FirstChildElement();
					if (child->Value() == string("image"))
					{
						TileSource tileSource;
						child->Attribute("width", &tileSource.Width);
						child->Attribute("height", &tileSource.Height);
						tileSource.SourceFile = child->Attribute("source");
						tileSource.Name = tileset.Name + to_string(tileId);
						tileset.TileSourceMap[tileId] = tileSource;
					}
				}

			}
		}
	}
	
	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesetList, int tileSize, int rowCount, int colCount)
{
	TiXmlElement* data = nullptr;
	string name = xmlLayer->Attribute("name");
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		auto val = e->Value();
		if (e->Value() == string("data"))
		{
			data = e;
			break;
		}
	}

	string matrix(data->GetText());
	istringstream iss(matrix);
	string id;
	TileMap tileMap(rowCount, vector<int>(colCount, 0));

	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++)
		{
			getline(iss, id, ',');
			stringstream converter(id);
			converter >> tileMap[row][col];
			if (!iss.good())
				break;
		}
	}

	return new TileLayer(name, tileSize, rowCount, colCount, tileMap, tilesetList);
}
