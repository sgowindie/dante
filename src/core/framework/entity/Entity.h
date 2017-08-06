//
//  Entity.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/3/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Entity__
#define __noctisgames__Entity__

#include "Color.h"
#include "FrameworkConstants.h"

#include "Box2D/Common/b2Math.h"

#include "RTTI.h"

#include <stdint.h>

class b2World;
struct b2Vec2;
class b2Body;
class b2Fixture;
class b2Contact;
class OutputMemoryBitStream;
class InputMemoryBitStream;

#define NW_TYPE_DECL(inCode) \
public: \
enum { kClassId = inCode }; \
virtual uint32_t getNetworkType();

#define NW_TYPE_IMPL(name) \
uint32_t name::getNetworkType() { return kClassId; }

struct EntityDef
{
    EntityDef()
    {
        restitution = 0.0f;
        density = 1.0f;
        isStaticBody = true;
        fixedRotation = true;
        bullet = false;
        isSensor = false;
        isCharacter = false;
    }
    
    float restitution;
    float density;
    bool isStaticBody;
    bool fixedRotation;
    bool bullet;
    bool isSensor;
    bool isCharacter;
};

class Entity
{
    RTTI_DECL;
    
    NW_TYPE_DECL(NW_TYPE_Entity);
    
public:
    Entity(b2World& world, float x, float y, float width, float height, bool isServer, EntityDef inEntityDef);
    
    virtual ~Entity();
    
    virtual EntityDef constructEntityDef() = 0;
    
    virtual void update() = 0;
    
    virtual bool shouldCollide(Entity* inEntity, b2Fixture* inFixtureA, b2Fixture* inFixtureB) = 0;
    
    virtual void handleBeginContact(Entity* inEntity, b2Fixture* inFixtureA, b2Fixture* inFixtureB) = 0;
    
    virtual void handleEndContact(Entity* inEntity, b2Fixture* inFixtureA, b2Fixture* inFixtureB) = 0;
    
    virtual uint32_t getAllStateMask() const = 0;
    
    virtual void read(InputMemoryBitStream& inInputStream) = 0;
    
    virtual uint32_t write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) = 0;
    
    void onDeletion();
    
    void handleBeginFootContact(Entity* inEntity);
    
    void handleEndFootContact(Entity* inEntity);
    
    void setStateTime(float stateTime);
    
    float getStateTime();
    
    b2Body* getBody();
    
    void setPosition(b2Vec2 position);
    
    const b2Vec2& getPosition();
    
    void setVelocity(b2Vec2 velocity);
    
    const b2Vec2& getVelocity();
    
    void setColor(Color color);
    
    Color& getColor();
    
    void setWidth(float width);
    
    const float& getWidth();
    
    void setHeight(float height);
    
    const float& getHeight();
    
    void setAngle(float angle);
    
    float getAngle();
    
    void setID(int inID);
    
    int getID();
    
    bool isGrounded();
    
    bool isFalling();
    
    void requestDeletion();
    
    bool isRequestingDeletion();
    
protected:
    b2World& m_worldRef;
    b2Body* m_body;
    b2Fixture* m_fixture;
    b2Fixture* m_footSensorFixture;
    float m_fStateTime;
    Color m_color;
    float m_fWidth;
    float m_fHeight;
    bool m_isServer;
    
    // Cached Last Known Values (from previous frame)
    b2Vec2 m_velocityLastKnown;
    b2Vec2 m_positionLastKnown;
    
    void interpolateClientSidePrediction(b2Vec2& inOldVelocity, b2Vec2& inOldPos);
    
    bool interpolateVectorsIfNecessary(b2Vec2& inA, const b2Vec2& inB, float& syncTracker, const char* vectorType);
    
private:
    float m_fTimeVelocityBecameOutOfSync;
    float m_fTimePositionBecameOutOfSync;
    int m_iID;
    int m_iNumGroundContacts;
    bool m_isRequestingDeletion;
    
    static int getUniqueEntityID();
};

#endif /* defined(__noctisgames__Entity__) */
