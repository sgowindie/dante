//
//  SocketAddress.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SocketAddress__
#define __noctisgames__SocketAddress__

#include "NetworkConstants.h"

#include <memory>
#include <string>

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort)
    {
        GetAsSockAddrIn()->sin_family = AF_INET;
        GetIP4Ref() = htonl(inAddress);
        GetAsSockAddrIn()->sin_port = htons(inPort);
    }
    
    SocketAddress(const sockaddr& inSockAddr)
    {
        memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
    }
    
    SocketAddress()
    {
        GetAsSockAddrIn()->sin_family = AF_INET;
        GetIP4Ref() = INADDR_ANY;
        GetAsSockAddrIn()->sin_port = 0;
    }
    
    bool operator==(const SocketAddress& inOther) const
    {
        return (mSockAddr.sa_family == AF_INET &&
                GetAsSockAddrIn()->sin_port == inOther.GetAsSockAddrIn()->sin_port) &&
        (GetIP4Ref() == inOther.GetIP4Ref());
    }
    
    size_t GetHash() const
    {
        return (GetIP4Ref()) |
        ((static_cast<uint32_t>(GetAsSockAddrIn()->sin_port)) << 13) |
        mSockAddr.sa_family;
    }
    
    
    uint32_t				GetSize()			const	{ return sizeof(sockaddr); }
    
    std::string					ToString()			const;
    
private:
    friend class UDPSocket;
    
    sockaddr mSockAddr;
#if _WIN32
    uint32_t&				GetIP4Ref()					{ return *reinterpret_cast< uint32_t* >(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
    const uint32_t&			GetIP4Ref()			const	{ return *reinterpret_cast< const uint32_t* >(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
#else
    uint32_t&				GetIP4Ref()					{ return GetAsSockAddrIn()->sin_addr.s_addr; }
    const uint32_t&			GetIP4Ref()			const	{ return GetAsSockAddrIn()->sin_addr.s_addr; }
#endif
    
    sockaddr_in*			GetAsSockAddrIn()			{ return reinterpret_cast< sockaddr_in* >(&mSockAddr); }
    const	sockaddr_in*	GetAsSockAddrIn()	const	{ return reinterpret_cast< const sockaddr_in* >(&mSockAddr); }
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

namespace std
{
    template<> struct hash< SocketAddress >
    {
        size_t operator()(const SocketAddress& inAddress) const
        {
            return inAddress.GetHash();
        }
    };
}

#endif /* defined(__noctisgames__SocketAddress__) */
