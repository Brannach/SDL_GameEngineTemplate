#pragma once

#include <memory>
#include <vector>

#include "Layer.h"
#include "TileLayer.h"
#include "../Entities/Actor.h"

using namespace std;

class GameMap
{
public:
	void Render()
	{
		for (size_t i = 0; i < mMapLayers.size(); i++)
			mMapLayers[i]->Render();
	}
	void Update()
	{
		for (size_t i = 0; i < mMapLayers.size(); i++)
			mMapLayers[i]->Update();
	}
	
	vector<unique_ptr<Actor>> SpawnActors()
	{
		vector<unique_ptr<Actor>> actors;
		for (auto& layer : mMapLayers)
		{
			if (auto* tl = dynamic_cast<TileLayer*>(layer.get()))
			{
				auto spawned = tl->SpawnActors();
				for (auto& a : spawned)
					actors.push_back(move(a));
			}
		}
		return actors;
	}

	inline int GetColCount()	{ return mColCount; }
	inline int GetRowCount()	{ return mRowCount; }
	inline int GetTileSize() { return mTileSize; }
	inline int GetMapWidth()	{ return mColCount * (mTileSize); }
	inline int GetMapHeight()	{ return mRowCount * (mTileSize); }
	inline const vector<unique_ptr<Layer>>& GetLayers() { return mMapLayers; }
	
private:
	friend class MapParser;
	vector<unique_ptr<Layer>> mMapLayers;
	int mRowCount, mColCount, mTileSize;
	
};

