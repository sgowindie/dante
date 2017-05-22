//
//  Engine.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Engine.h"

#include "SocketUtil.h"
#include "GameObjectRegistry.h"
#include "World.h"

#include <time.h>
#include <stdlib.h>

std::unique_ptr<Engine>	Engine::sInstance;

Engine::Engine() :
mShouldKeepRunning(true)
{
    SocketUtil::StaticInit();
    
    srand(static_cast<uint32_t>(time(nullptr)));
    
    GameObjectRegistry::StaticInit();
    
    World::StaticInit();
}

Engine::~Engine()
{
    SocketUtil::CleanUp();
}

int Engine::Run()
{
    // Override this
    return -2;
}

void Engine::DoFrame()
{
    World::sInstance->Update();
}
