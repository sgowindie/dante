//
//  DirectXTextureLoader.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "framework/graphics/directx/DirectXTextureLoader.h"

#include "framework/graphics/portable/GpuTextureDataWrapper.h"
#include <framework/graphics/portable/TextureWrapper.h>
#include "framework/graphics/portable/GpuTextureWrapper.h"

#include "framework/util/macros.h"
#include "framework/graphics/directx/DirectXManager.h"
#include "framework/file/portable/AssetDataHandler.h"
#include "framework/file/portable/FileData.h"
#include "framework/util/StringUtil.h"

#include "DDSTextureLoader.h"
#include "PlatformHelpers.h"

#include <string>

DirectXTextureLoader::DirectXTextureLoader() : TextureLoader()
{
    // Empty
}

DirectXTextureLoader::~DirectXTextureLoader()
{
    // Empty
}

GpuTextureDataWrapper* DirectXTextureLoader::loadTextureData(TextureWrapper* textureWrapper)
{
    const char* textureName = textureWrapper->name.c_str();

	std::string s("data\\textures\\");
	s += std::string(textureName);
	const char* finalPath = s.c_str();
    
    const FileData dds_file = AssetDataHandler::getAssetDataHandler()->getAssetData(finalPath);
    void* output = NULL;
    if (textureWrapper->_isEncrypted)
    {
        malloc(dds_file.data_length);
        StringUtil::encryptDecrypt((unsigned char*)dds_file.data, (unsigned char*) output, dds_file.data_length);
    }
    else
    {
        output = (void*) dds_file.data;
    }
    
    ID3D11ShaderResourceView *pShaderResourceView;
    
	ID3D11Device* d3dDevice = DirectXManager::getD3dDevice();
    DirectX::ThrowIfFailed(DirectX::CreateDDSTextureFromMemory(d3dDevice, (const uint8_t*)output, dds_file.data_length, NULL, &pShaderResourceView));
    
    AssetDataHandler::getAssetDataHandler()->releaseAssetData(&dds_file);
    
    GpuTextureDataWrapper* tdw = new GpuTextureDataWrapper(pShaderResourceView);
    
    if (textureWrapper->_isEncrypted)
    {
        free((void *)output);
    }
    
    return tdw;
}

GpuTextureWrapper* DirectXTextureLoader::loadTexture(GpuTextureDataWrapper* textureData, bool repeatS)
{
    UNUSED(repeatS);
    
    return new GpuTextureWrapper(textureData->texture);
}
