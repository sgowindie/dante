//
//  NGLightingShader.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/18.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "framework/graphics/portable/NGLightingShader.h"

#include <framework/graphics/portable/RendererHelper.h>
#include <framework/graphics/portable/NGShaderLoader.h>
#include <framework/graphics/portable/NGShaderUniformInput.h>
#include <framework/graphics/portable/NGShaderVarInput.h>
#include <framework/graphics/portable/ShaderProgramWrapper.h>
#include <framework/util/Config.h>

#include <assert.h>

NGLightingShader::NGLightingShader(RendererHelper& inRendererHelper, const char* vertexShaderName, const char* fragmentShaderName) : NGShader(inRendererHelper, vertexShaderName, fragmentShaderName),
_defaultLightZ(NG_CFG->getFloat("defaultLightZ"))
{
    _resolution[0] = 1440.0f;
    _resolution[1] = 900.0f;
    
    _lights[0][0] = 0;
    _lights[0][1] = 0;
    _lights[0][2] = _defaultLightZ;
    _lights[0][3] = 0;
    
    _lightColor[0] = NG_CFG->getFloat("LightColorR");
    _lightColor[1] = NG_CFG->getFloat("LightColorG");
    _lightColor[2] = NG_CFG->getFloat("LightColorB");
    _lightColor[3] = NG_CFG->getFloat("LightColorA");
    
    _ambientColor[0] = NG_CFG->getFloat("AmbientColorR");
    _ambientColor[1] = NG_CFG->getFloat("AmbientColorG");
    _ambientColor[2] = NG_CFG->getFloat("AmbientColorB");
    _ambientColor[3] = NG_CFG->getFloat("AmbientColorA");
    
    _fallOff[0] = NG_CFG->getFloat("LightFalloffX");
    _fallOff[1] = NG_CFG->getFloat("LightFalloffY");
    _fallOff[2] = NG_CFG->getFloat("LightFalloffZ");
    _fallOff[3] = 0;
    
    // Vertex Shader
    _uniforms.push_back(new NGShaderUniformInput("u_Matrix",        0, 64, false));
    _uniforms.push_back(new NGShaderUniformInput("u_Lights",        1, 64, false));
    
    // Fragment Shader
    _uniforms.push_back(new NGShaderUniformInput("u_LightColor",    2, 16, true));
    _uniforms.push_back(new NGShaderUniformInput("u_AmbientColor",  3, 16, true));
    _uniforms.push_back(new NGShaderUniformInput("u_Falloff",       4, 16, true));
    _uniforms.push_back(new NGShaderUniformInput("u_Resolution",    5,  8, true));

    _uniforms.push_back(new NGShaderUniformInput("u_TextureUnit",   6));
    _uniforms.push_back(new NGShaderUniformInput("u_NormalMapUnit", 7));
    
    _inputLayout.push_back(new NGShaderVarInput("a_Position", 2, 0));
    _inputLayout.push_back(new NGShaderVarInput("a_Color", 4, 2));
    _inputLayout.push_back(new NGShaderVarInput("a_TexCoord", 2, 6));
}

void NGLightingShader::bind(void* vertices, void* data1, void* data2)
{
    assert(vertices != NULL);
    assert(data1 != NULL);
    assert(data2 != NULL);
    
    _rendererHelper.bindNGShader(_shaderProgramWrapper);
    _rendererHelper.bindMatrix(                                                     _uniforms[0]);
    _rendererHelper.bindMatrix(                                                     _uniforms[1], _lights);
    _rendererHelper.bindVector4(                                                    _uniforms[2], _lightColor);
    _rendererHelper.bindVector4(                                                    _uniforms[3], _ambientColor);
    _rendererHelper.bindVector4(                                                    _uniforms[4], _fallOff);
    _rendererHelper.bindVector2(                                                    _uniforms[5], _resolution);
    _rendererHelper.bindTexture(NGTextureSlot_ZERO, static_cast<NGTexture*>(data1), _uniforms[6]);
    _rendererHelper.bindTexture(NGTextureSlot_ONE, static_cast<NGTexture*>(data2),  _uniforms[7]);
    
    std::vector<TEXTURE_VERTEX>* textureVertices = static_cast<std::vector<TEXTURE_VERTEX>* >(vertices);
    _rendererHelper.mapTextureVertices(_inputLayout, *textureVertices);
}

void NGLightingShader::unbind()
{
    _rendererHelper.unmapScreenVertices();
    _rendererHelper.bindTexture(NGTextureSlot_ZERO, NULL);
    _rendererHelper.bindTexture(NGTextureSlot_ONE, NULL);
    _rendererHelper.bindNGShader(NULL);
}

void NGLightingShader::configResolution(float resolutionX, float resolutionY)
{
    _resolution[0] = resolutionX;
    _resolution[1] = resolutionY;
}

void NGLightingShader::resetLights()
{
    for (int i = 0; i < 4; ++i)
    {
        _lights[i][3] = 0;
    }
}

void NGLightingShader::configLight(int index, float lightPosX, float lightPosY)
{
    _lights[index][0] = lightPosX;
    _lights[index][1] = lightPosY;
    _lights[index][2] = _defaultLightZ;
    _lights[index][3] = 1;
}

void NGLightingShader::configZ(float lightPosZ)
{
    for (int i = 0; i < 4; ++i)
    {
        _lights[i][2] = lightPosZ;
    }
}
