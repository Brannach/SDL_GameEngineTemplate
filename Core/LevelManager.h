#pragma once
#include <vector>
#include <memory>
#include "ILevel.h"

class LevelManager
{
public:
    LevelManager();
    void AddLevel(std::unique_ptr<ILevel> level);

    void LoadCurrent();
    bool AdvanceLevel();
    void Restart();

    bool IsCurrentComplete() const;
    bool HasNextLevel() const;
    ILevel& GetCurrentLevel();
    int GetLevelCount() const;
    int GetCurrentLevelIndex() const;

private:
    std::vector<std::unique_ptr<ILevel>> mLevels;
    int mCurrentIndex = 0;
};
