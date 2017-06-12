//
//  SteamGameServices.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 6/11/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SteamGameServices__
#define __noctisgames__SteamGameServices__

#ifdef STEAM_CEG
// Steam DRM header file
#include "cegclient.h"
#else
#define Steamworks_InitCEGLibrary() (true)
#define Steamworks_TermCEGLibrary()
#define Steamworks_TestSecret()
#define Steamworks_SelfCheck()
#endif

class SteamGameServices
{
public:
    static SteamGameServices* getInstance();
    
    bool init();
    
    void deinit();
    
private:
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    SteamGameServices();
    virtual ~SteamGameServices();
    SteamGameServices(const SteamGameServices&);
    SteamGameServices& operator=(const SteamGameServices&);
};

#endif /* defined(__noctisgames__SteamGameServices__) */
