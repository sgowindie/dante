//
//  StudioRenderer.h
//  dante
//
//  Created by Stephen Gowen on 1/4/18.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__StudioRenderer__
#define __noctisgames__StudioRenderer__

#include "framework/graphics/portable/Renderer.h"

#include "framework/graphics/portable/FontAlign.h"
#include "framework/math/Vector2.h"

#include <string>
#include <deque>

class TextureManager;
class SpriteBatcher;
class PolygonBatcher;
class LineBatcher;
class CircleBatcher;
class NGShaderLoader;
class RendererHelper;
class NGShader;
class Entity;
class TextureRegion;
class Color;
class NGRect;
class NGTexture;
class Font;
class World;
class StudioEngine;
class Box2DDebugRenderer;

#define NUM_SPRITE_BATCHERS 8
#define NUM_CAMERAS 4

class StudioRenderer : public Renderer
{
public:
    StudioRenderer();
    virtual ~StudioRenderer();
    
    virtual void createDeviceDependentResources();
    virtual void createWindowSizeDependentResources(int screenWidth, int screenHeight, int renderWidth, int renderHeight);
    virtual void releaseDeviceDependentResources();
    virtual void render(int flags = 0);
    
    void update(float x, float y, float w, float h, int scale);
    void setWorld(World* inValue);
    void displayToast(std::string toast);
    
private:
    TextureManager* _textureManager;
    RendererHelper* _rendererHelper;
    SpriteBatcher* _spriteBatchers[NUM_SPRITE_BATCHERS];
    PolygonBatcher* _fillPolygonBatcher;
    PolygonBatcher* _boundsPolygonBatcher;
    LineBatcher* _lineBatcher;
    CircleBatcher* _circleBatcher;
    Box2DDebugRenderer* _box2DDebugRenderer;
    NGShaderLoader* _shaderProgramLoader;
    Font* _font;
    NGShader* _textureNGShader;
    NGShader* _colorNGShader;
    NGShader* _framebufferToScreenNGShader;
    NGRect* _camBounds[NUM_CAMERAS];
    World* _world;
    std::deque<std::string> _toasts;
    int _toastStateTime;
    int _fbIndex;
    int _scrollValue;
    
    void setFramebuffer(int framebufferIndex, float r = 0, float g = 0, float b = 0, float a = 0);
    void renderWorld();
    void renderLayers();
    void renderEntities();
    void renderBox2D();
    void renderGrid();
    void renderUI(int flags);
    void renderText(const char* inStr, float x, float y, const Color& inColor, int justification = FONT_ALIGN_LEFT);
    void endFrame();
};

#endif /* defined(__noctisgames__StudioRenderer__) */
