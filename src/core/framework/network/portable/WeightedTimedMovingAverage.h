//
//  WeightedTimedMovingAverage.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__WeightedTimedMovingAverage__
#define __noctisgames__WeightedTimedMovingAverage__

class WeightedTimedMovingAverage
{
public:
    WeightedTimedMovingAverage(float inDuration = 5.f);
    
    void UpdatePerSecond(float inValue);
    
    void Update(float inValue);
    
    float GetValue() const;
    
private:
    float m_fTimeLastEntryMade;
    float m_fValue;
    float m_fDuration;
};

#endif /* defined(__noctisgames__WeightedTimedMovingAverage__) */
