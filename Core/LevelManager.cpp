#include "LevelManager.h"

#include "BreakoutLevel.h"

LevelManager::LevelManager()
{
    mLevels.push_back(make_unique<BreakoutLevel>("Map01", "./Resources/Maps/Map01.tmx"));
    mLevels.push_back(make_unique<BreakoutLevel>("Map02", "./Resources/Maps/Map02.tmx"));
    mLevels.push_back(make_unique<BreakoutLevel>("Map03", "./Resources/Maps/Map03.tmx"));
}

void LevelManager::AddLevel(std::unique_ptr<ILevel> level)
{
    mLevels.push_back(std::move(level));
}

void LevelManager::LoadCurrent()
{
    mLevels[mCurrentIndex]->Load();
}

bool LevelManager::AdvanceLevel()
{
    if (mCurrentIndex + 1 >= static_cast<int>(mLevels.size()))
        return false;
    mLevels[mCurrentIndex]->Unload();
    mCurrentIndex++;
    mLevels[mCurrentIndex]->Load();
    return true;
}

void LevelManager::Restart()
{
    mLevels[mCurrentIndex]->Unload();
    mCurrentIndex = 0;
    mLevels[mCurrentIndex]->Load();
}

bool LevelManager::IsCurrentComplete() const
{
    return mLevels[mCurrentIndex]->IsComplete();
}

bool LevelManager::HasNextLevel() const
{
    return mCurrentIndex + 1 < static_cast<int>(mLevels.size());
}

ILevel& LevelManager::GetCurrentLevel()
{
    return *mLevels[mCurrentIndex];
}

int LevelManager::GetCurrentLevelIndex() const
{
    return mCurrentIndex;
}

int LevelManager::GetLevelCount() const
{
    return static_cast<int>(mLevels.size());
}

