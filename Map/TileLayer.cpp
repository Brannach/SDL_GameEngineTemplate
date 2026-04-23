#include "TileLayer.h"
#include "..\Rendering\TextureRenderer.h"
#include "..\Entities\Brick.h"

TileLayer::TileLayer(string name, int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tileSetList)
	: mTileSets (tileSize)
{
	mRowCount = rowCount;
	mColCount = colCount;
	mTileMap = tileMap;
	mTileSets = tileSetList;
	mTileSize = tileSize;

	mName = name;

	for (size_t i = 0; i < mTileSets.size(); i++)
	{
		if (mTileSets[i].Sourcefile != "")
		{
			TextureRenderer::GetInstance().Load(mTileSets[i].Name, "resources/Maps/" + mTileSets[i].Sourcefile, Engine::GetInstance().GetRenderer());
		}
		else
		{
			for (auto tileSource : mTileSets[i].TileSourceMap)
			{
				TextureRenderer::GetInstance().Load(tileSource.second.Name, "Resources/Maps/" + tileSource.second.SourceFile, Engine::GetInstance().GetRenderer());
			}
		}
	}
}

void TileLayer::Render()
{
	for (int row = 0; row < mRowCount; row++)
	{
		for (int col = 0; col < mColCount; col++)
		{
			int tileId = mTileMap[row][col];
			if (tileId == 0) continue;

			int tilesetIndex = 0;
			if (mTileSets.size() > 1)
			{
				for (size_t k = 1; k < mTileSets.size(); k++)
				{
					if (tileId > mTileSets[k].FirstID && tileId < mTileSets[k].LastID)
					{
						tileId = tileId + mTileSets[k].TileCount - mTileSets[k].LastID;
						tilesetIndex = k;
						break;
					}
				}
			}
			Tileset tileSet = mTileSets[tilesetIndex];
			if (tileSet.TileSourceMap.size() != 0)
				continue;   // brick tiles — rendered by their own Actor::Draw(), skip here

			int tileRow = tileId / tileSet.ColCount;
			int tileCol = tileId - tileRow * tileSet.ColCount - 1;
			if (tileId % tileSet.ColCount == 0)
			{
				tileRow--;
				tileCol = tileSet.ColCount - 1;
			}
			TextureRenderer::GetInstance().DrawAnimationTile(
				tileSet.Name, tileSet.TileSize,
				col * tileSet.TileWidth, row * tileSet.TileHeight,
				tileRow, tileCol, SDL_FLIP_NONE, Engine::GetInstance().GetRenderer());
		}
	}
}

vector<unique_ptr<Actor>> TileLayer::SpawnActors()
{
	vector<unique_ptr<Actor>> actors;
	Dimension2d mainWindowSize = Engine::GetInstance().GetMainApplication()->MainWindowDimension;

	for (int row = 0; row < mRowCount; row++)
	{
		for (int col = 0; col < mColCount; col++)
		{
			int tileId = mTileMap[row][col];
			if (tileId == 0) continue;

			int tilesetIndex = 0;
			if (mTileSets.size() > 1)
			{
				for (size_t k = 1; k < mTileSets.size(); k++)
				{
					if (tileId > mTileSets[k].FirstID && tileId < mTileSets[k].LastID)
					{
						tileId = tileId + mTileSets[k].TileCount - mTileSets[k].LastID;
						tilesetIndex = k;
						break;
					}
				}
			}
			Tileset tileSet = mTileSets[tilesetIndex];
			if (tileSet.TileSourceMap.size() == 0) continue;  // not a brick tile layer

			int scaledTileWidth  = mainWindowSize.width  / static_cast<int>(mTileMap[0].size());
			int scaledTileHeight = mainWindowSize.height / static_cast<int>(mTileMap.size());
			int scaledTileX = col * scaledTileWidth;
			int scaledTileY = row * scaledTileHeight;
			string tileSetName = tileSet.TileSourceMap[tileId - 1].Name;

			actors.push_back(make_unique<Brick>(
				Properties(tileSetName, scaledTileX, scaledTileY, scaledTileWidth, scaledTileHeight)));
		}
	}
	return actors;
}

void TileLayer::Update()
{
}
