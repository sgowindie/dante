//
//  InputMemoryBitStream.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "InputMemoryBitStream.h"

#include "Vector2.h"
#include "Box2D/Box2D.h"
#include "Color.h"

#include <cstring>	// memcpy()

InputMemoryBitStream::InputMemoryBitStream(char* inBuffer, uint32_t inBitCount) :
m_buffer(inBuffer),
m_iBitCapacity(inBitCount),
m_iBitHead(0),
m_isBufferOwner(false)
{
    // Empty
}

InputMemoryBitStream::InputMemoryBitStream(const InputMemoryBitStream& inOther) :
m_iBitCapacity(inOther.m_iBitCapacity),
m_iBitHead(inOther.m_iBitHead),
m_isBufferOwner(true)
{
    //allocate buffer of right size
    int byteCount = (m_iBitCapacity + 7) / 8;
    m_buffer = static_cast<char*>(malloc(byteCount));
    //copy
    memcpy(m_buffer, inOther.m_buffer, byteCount);
}

InputMemoryBitStream::~InputMemoryBitStream()
{
    if (m_isBufferOwner)
    {
        free(m_buffer);
    }
}

const char*	InputMemoryBitStream::getBufferPtr() const
{
    return m_buffer;
}

uint32_t InputMemoryBitStream::getRemainingBitCount() const
{
    return m_iBitCapacity - m_iBitHead;
}

void InputMemoryBitStream::readBits(uint8_t& outData, uint32_t inBitCount)
{
    uint32_t byteOffset = m_iBitHead >> 3;
    uint32_t bitOffset = m_iBitHead & 0x7;
    
    outData = static_cast<uint8_t>(m_buffer[byteOffset]) >> bitOffset;
    
    uint32_t bitsFreeThisByte = 8 - bitOffset;
    if (bitsFreeThisByte < inBitCount)
    {
        //we need another byte
        outData |= static_cast<uint8_t>(m_buffer[byteOffset + 1]) << bitsFreeThisByte;
    }
    
    //don't forget a mask so that we only read the bit we wanted...
    outData &= (~(0x00ff << inBitCount));
    
    m_iBitHead += inBitCount;
}

void InputMemoryBitStream::readBits(void* outData, uint32_t inBitCount)
{
    uint8_t* destByte = reinterpret_cast< uint8_t* >(outData);
    // read all the bytes
    while (inBitCount > 8)
    {
        readBits(*destByte, 8);
        ++destByte;
        inBitCount -= 8;
    }
    
    // read anything left
    if (inBitCount > 0)
    {
        readBits(*destByte, inBitCount);
    }
}

void InputMemoryBitStream::readBytes(void* outData, uint32_t inByteCount)
{
    readBits(outData, inByteCount << 3);
}

void InputMemoryBitStream::read(uint32_t& outData, uint32_t inBitCount)
{
    readBits(&outData, inBitCount);
    
    outData = ntohl(outData);
}

void InputMemoryBitStream::read(int& outData, uint32_t inBitCount)
{
    readBits(&outData, inBitCount);
    
    outData = ntohl(outData);
}

void InputMemoryBitStream::read(float& outData)
{
    readBits(&outData, 32);
    
    outData = float_swap(outData, false);
}

void InputMemoryBitStream::readSignedBinaryValue(float& outValue)
{
    bool isNonZero;
    read(isNonZero);
    if (isNonZero)
    {
        bool isPositive;
        read(isPositive);
        outValue = isPositive ? 1.f : -1.f;
    }
    else
    {
        outValue = 0.f;
    }
}

void InputMemoryBitStream::read(uint16_t& outData, uint32_t inBitCount)
{
    readBits(&outData, inBitCount);
    
    outData = ntohs(outData);
}

void InputMemoryBitStream::read(int16_t& outData, uint32_t inBitCount)
{
    readBits(&outData, inBitCount);
    
    outData = ntohs(outData);
}

void InputMemoryBitStream::read(uint8_t& outData, uint32_t inBitCount)
{
    readBits(&outData, inBitCount);
}

void InputMemoryBitStream::read(bool& outData)
{
    readBits(&outData, 1);
}

void InputMemoryBitStream::resetToCapacity(uint32_t inByteCapacity)
{
    m_iBitCapacity = inByteCapacity << 3; m_iBitHead = 0;
}

void InputMemoryBitStream::read(std::string& inString)
{
    uint32_t elementCount;
    read(elementCount);
    
    elementCount = ntohl(elementCount);
    
    inString.resize(elementCount);
    for (auto& element : inString)
    {
        read(element);
    }
}

void InputMemoryBitStream::read(Vector2& outVector)
{
    read(outVector.getXRef());
    read(outVector.getYRef());
}

void InputMemoryBitStream::read(b2Vec2& outVector)
{
    bool isZero;
    read(isZero);
    if (isZero)
    {
        outVector.x = 0;
    }
    else
    {
        read(outVector.x);
    }
    
    read(isZero);
    if (isZero)
    {
        outVector.y = 0;
    }
    else
    {
        read(outVector.y);
    }
}

void InputMemoryBitStream::read(Color& outColor)
{
    read(outColor.red);
    read(outColor.green);
    read(outColor.blue);
    read(outColor.alpha);
}
