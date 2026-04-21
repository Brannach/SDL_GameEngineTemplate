#include "BreakoutLevel.h"
#include "Engine.h"
#include "../Map/MapParser.h"
#include "../Rendering/TextureRenderer.h"
#include "../Entities/BouncingBall.h"
#include "../Entities/Paddle.h"
#include "../Entities/Health.h"
#include "../Entities/Brick.h"

BreakoutLevel::BreakoutLevel(std::string mapId, std::string mapFile)
    : mMapId(mapId), mMapFile(mapFile) {}

void BreakoutLevel::Load()
{
    TextureRenderer::GetInstance().Load("ball",    "./Resources/Actors/ball_marble.png", Engine::GetInstance().GetRenderer());
    TextureRenderer::GetInstance().Load("paddle",  "./Resources/Actors/paddle.png",      Engine::GetInstance().GetRenderer());
    TextureRenderer::GetInstance().Load("health",  "./Resources/Actors/health.png",      Engine::GetInstance().GetRenderer());

    mActors.push_back(make_unique<BouncingBall>(Properties("ball",    400, 475,  24,  24)));
    mActors.push_back(make_unique<Paddle>      (Properties("paddle",  350, 500, 100,  25)));
    mActors.push_back(make_unique<Health>      (Properties("health",  700, 550,  20,  20)));

    mMap = MapParser::GetInstance().Load(mMapId, mMapFile);

    for (auto& actor : mMap->SpawnActors())
        mActors.push_back(move(actor));
}

void BreakoutLevel::Unload()
{
    mActors.clear();
    mMap.reset();
}

void BreakoutLevel::Update(float delta)
{
    for (const auto& actor : mActors)
        actor->Update(delta);
}

void BreakoutLevel::Render()
{
    mMap->Render();
    for (const auto& actor : mActors)
        actor->Draw();
}

bool BreakoutLevel::IsComplete()
{
    for (const auto& actor : mActors)
        if (dynamic_cast<Brick*>(actor.get()) != nullptr)
            return false;
    return true;
}

const std::list<std::unique_ptr<Actor>>& BreakoutLevel::GetActors()
{
    return mActors;
}

void BreakoutLevel::AddActor(std::unique_ptr<Actor> actor)
{
    mActors.push_back(std::move(actor));
}

void BreakoutLevel::RemoveActor(Actor* actor)
{
    erase_if(mActors, [actor](const std::unique_ptr<Actor>& a) { return a.get() == actor; });
}