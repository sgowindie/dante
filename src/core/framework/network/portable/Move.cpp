//
//  Move.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Move.h"

#include "IInputState.h"
#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

Move::Move(IInputState* inInputState, float inTimestamp, float inDeltaTime) :
m_inputState(inInputState),
m_fTimestamp(inTimestamp),
m_fDeltaTime(inDeltaTime)
{
    // Empty
}

Move::Move() : m_inputState(nullptr), m_fTimestamp(0), m_fDeltaTime(0)
{
    // Empty
}

bool Move::write(OutputMemoryBitStream& inOutputStream) const
{
    if (m_inputState)
    {
        m_inputState->write(inOutputStream);
    }
    
    inOutputStream.write(m_fTimestamp);
    
    return true;
}

bool Move::read(InputMemoryBitStream& inInputStream)
{
    if (m_inputState)
    {
        m_inputState->read(inInputStream);
    }
    
    inInputStream.read(m_fTimestamp);
    
    return true;
}

IInputState* Move::getInputState() const
{
    return m_inputState;
}

float Move::getTimestamp() const
{
    return m_fTimestamp;
}

float Move::getDeltaTime() const
{
    return m_fDeltaTime;
}
