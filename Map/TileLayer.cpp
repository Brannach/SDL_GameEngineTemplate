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
			TextureRenderer::GetInstance()->Load(mTileSets[i].Name, "resources/Maps/" + mTileSets[i].Sourcefile, Engine::GetInstance()->GetRenderer());
		}
		else
		{
			for (auto tileSource : mTileSets[i].TileSourceMap)
			{
				TextureRenderer::GetInstance()->Load(tileSource.second.Name, "Resources/Maps/" + tileSource.second.SourceFile, Engine::GetInstance()->GetRenderer());
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
			if (tileId != 0)
			{
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
				int tileRow = tileId / tileSet.ColCount;
				int tileCol = tileId - tileRow * tileSet.ColCount - 1;
				if (tileId % tileSet.ColCount == 0)
				{
					tileRow--;
					tileCol = tileSet.ColCount - 1;
				}
				string tileSetName = tileSet.Name;
				if (tileSet.TileSourceMap.size() != 0)
				{
					Dimension2d mainWindowSize = Engine::GetInstance()->GetMainApplication()->MainWindowDimension;
					tileSetName = tileSet.TileSourceMap[tileId - 1].Name;
					int scaledTileWidth = mainWindowSize.width / mTileMap[0].size();
					int scaledTileHeight = mainWindowSize.height / mTileMap.size();
					int scaledTileX = col * scaledTileWidth;
					int scaledTileY = row * scaledTileHeight;
					Brick* tile = new Brick(Properties(tileSetName, scaledTileX, scaledTileY, scaledTileWidth, scaledTileHeight));
					Engine::GetInstance()->AddRenderedActor(tile);
					
					//TextureRenderer::GetInstance()->DrawTile(tileSetName, tileSet.TileWidth, tileSet.TileHeight, col * tileSet.TileWidth, row * tileSet.TileHeight, SDL_FLIP_NONE);
				}
				else
					TextureRenderer::GetInstance()->DrawAnimationTile(tileSetName, tileSet.TileSize, col * tileSet.TileWidth, row * tileSet.TileHeight, tileRow, tileCol, SDL_FLIP_NONE);
			}
		}
	}
}

void TileLayer::Update()
{
}
