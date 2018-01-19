//
//  NGShaderUniformInput.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 12/17/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "framework/graphics/portable/NGShaderUniformInput.h"

#include "framework/graphics/portable/ShaderProgramWrapper.h"

#if defined _WIN32
#include "framework/graphics/directx/DirectXRendererHelper.h"
#endif

NGShaderUniformInput::NGShaderUniformInput(const char* attribName, int index, int byteWidth, bool isFragment) : _attribName(attribName), _index(index), _byteWidth(byteWidth), _isFragment(isFragment)
{
    // Empty
}

void NGShaderUniformInput::build(ShaderProgramWrapper* inShaderProgramWrapper)
{
#if defined _WIN32
    if (_byteWidth > 0)
    {
        D3D11_BUFFER_DESC bd = { 0 };
        
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = _byteWidth;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        
        ID3D11Device* d3dDevice = DirectXRendererHelper::getD3dDevice();
        DX::ThrowIfFailed(d3dDevice->CreateBuffer(&bd, NULL, &_constantbuffer));
    }
#elif defined __APPLE__ || defined __ANDROID__ || defined __linux__
    _attribute = glGetUniformLocation(inShaderProgramWrapper->_programObjectId, _attribName);
#endif
}
