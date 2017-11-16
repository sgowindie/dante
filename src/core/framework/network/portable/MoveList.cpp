//
//  MoveList.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "MoveList.h"

#include "IInputState.h"
#include "Timing.h"
#include "StringUtil.h"

MoveList::MoveList(): m_fLastMoveTimestamp(-1.0f), m_fLastProcessedMoveTimestamp(-1.0f)
{
    // Empty
}

const Move& MoveList::addMove(IInputState* inInputState, float inTimestamp)
{
    m_moves.push_back(Move(inInputState, inTimestamp));
    
    m_fLastMoveTimestamp = inTimestamp;
    
    return m_moves.back();
}

bool MoveList::addMoveIfNew(const Move& inMove)
{
    //we might have already received this move in another packet (since we're sending the same move in multiple packets)
    //so make sure it's new...
    
    //adjust the deltatime and then place!
    float timeStamp = inMove.getTimestamp();
    
    if (timeStamp > m_fLastMoveTimestamp)
    {
        m_fLastMoveTimestamp = timeStamp;
        
        m_moves.push_back(Move(inMove.getInputState(), timeStamp));
        
        return true;
    }
    
    return false;
}

void MoveList::markMoveAsProcessed(Move* move)
{
    m_fLastProcessedMoveTimestamp = move->getTimestamp();
}

void MoveList::removeProcessedMoves(float inLastMoveProcessedOnServerTimestamp)
{
    while (!m_moves.empty() && m_moves.front().getTimestamp() <= inLastMoveProcessedOnServerTimestamp)
    {
		m_moves.front().getInputState()->setInUse(false);

        m_moves.pop_front();
    }
}

float MoveList::getLastMoveTimestamp() const
{
    return m_fLastMoveTimestamp;
}

float MoveList::getLastProcessedMoveTimestamp() const
{
    return m_fLastProcessedMoveTimestamp;
}

const Move& MoveList::getLatestMove() const
{
    return m_moves.back();
}

void MoveList::clear()
{
    m_moves.clear();
}

bool MoveList::hasMoves() const
{
    return !m_moves.empty();
}

uint32_t MoveList::getMoveCount() const
{
    return static_cast<uint32_t>(m_moves.size());
}

uint32_t MoveList::getNumMovesAfterTimestamp(float inLastMoveReceivedOnServerTimestamp) const
{
    uint32_t ret = 0;
    
    for (Move move : m_moves)
    {
        if (move.getTimestamp() > inLastMoveReceivedOnServerTimestamp)
        {
            ++ret;
        }
    }
    
    return ret;
}

Move* MoveList::getMoveAtIndex(uint32_t index)
{
    if (index < getMoveCount())
    {
        return &m_moves.at(index);
    }
    
    return nullptr;
}

std::deque<Move>::const_iterator MoveList::begin() const
{
    return m_moves.begin();
}

std::deque<Move>::const_iterator MoveList::end() const
{
    return m_moves.end();
}
