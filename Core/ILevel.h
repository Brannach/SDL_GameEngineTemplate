#pragma once
#include <list>
#include <memory>
#include "../Entities/Actor.h"

class ILevel
{
public:
    virtual ~ILevel() = default;
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Update(float delta) = 0;
    virtual void Render() = 0;
    virtual bool IsComplete() = 0;
    virtual const std::list<std::unique_ptr<Actor>>& GetActors() = 0;
};