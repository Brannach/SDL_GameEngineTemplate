#include <iostream>
#include <SDL.h>
#include "Engine.h"

int main(int argc, char* argv[])
{
    Engine* engine = Engine::GetInstance();
    engine->Run();

    return 0;
}
