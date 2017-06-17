//
//  FrameworkConstants.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/2/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__FrameworkConstants__
#define __noctisgames__FrameworkConstants__

//// Requested Action Definitions ////

#define REQUESTED_ACTION_UPDATE 0
#define REQUESTED_ACTION_EXIT -1

//// Shader Definitions ////

#define COLOR_VERTEX_SHADER "shader_001_vert"
#define COLOR_FRAGMENT_SHADER "shader_001_frag"
#define FRAMEBUFFER_TO_SCREEN_VERTEX_SHADER "shader_002_vert"
#define FRAMEBUFFER_TO_SCREEN_FRAGMENT_SHADER "shader_002_frag"
#define TEXTURE_VERTEX_SHADER "shader_003_vert"
#define TEXTURE_FRAGMENT_SHADER "shader_003_frag"

//// Network ////

#define NETWORK_TYPE_Entity 'ENTT'

#define NETWORK_PACKET_TYPE_HELLO 'HELO'
#define NETWORK_PACKET_TYPE_WELCOME 'WLCM'
#define NETWORK_PACKET_TYPE_STATE 'STAT'
#define NETWORK_PACKET_TYPE_INPUT 'INPT'

#define NETWORK_CLIENT_TIMEOUT 5.0f
#define NETWORK_ACK_TIMEOUT 0.5f

#define MAX_NUM_PLAYERS_PER_SERVER 4
#define NETWORK_MAX_NUM_PACKETS_PER_FRAME 16

#endif /* defined(__noctisgames__FrameworkConstants__) */
