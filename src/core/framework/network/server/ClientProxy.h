//
//  ClientProxy.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 5/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__ClientProxy__
#define __noctisgames__ClientProxy__

#include "ReplicationManagerServer.h"
#include "SocketAddress.h"
#include "DeliveryNotificationManager.h"
#include "MoveList.h"

class ClientProxy
{
public:
	ClientProxy(const SocketAddress& inSocketAddress, const std::string& inName, int inPlayerId);

	const	SocketAddress&	GetSocketAddress()	const	{ return mSocketAddress; }
			int				GetPlayerId()		const	{ return mPlayerId; }
	const	std::string&		GetName()			const	{ return mName; }

			void			SetInputState(const InputState& inInputState)		{ mInputState = inInputState; }
	const	InputState&		GetInputState()		const	{ return mInputState; }

			void			UpdateLastPacketTime();
			float			GetLastPacketFromClientTime()	const	{ return mLastPacketFromClientTime; }

			DeliveryNotificationManager&	GetDeliveryNotificationManager()	{ return mDeliveryNotificationManager; }
			ReplicationManagerServer&		GetReplicationManagerServer()		{ return mReplicationManagerServer; }

			const	MoveList&				GetUnprocessedMoveList() const		{ return mUnprocessedMoveList; }
					MoveList&				GetUnprocessedMoveList()			{ return mUnprocessedMoveList; }

			void	SetIsLastMoveTimestampDirty(bool inIsDirty)				{ mIsLastMoveTimestampDirty = inIsDirty; }
			bool	IsLastMoveTimestampDirty()						const		{ return mIsLastMoveTimestampDirty; }

			void	HandleCatDied();
			void	RespawnCatIfNecessary();

private:
	DeliveryNotificationManager	mDeliveryNotificationManager;
	ReplicationManagerServer mReplicationManagerServer;

	SocketAddress mSocketAddress;
	std::string mName;
	int mPlayerId;

	//going away!
	InputState mInputState;

	float mLastPacketFromClientTime;
	float mTimeToRespawn;

	MoveList mUnprocessedMoveList;
	bool mIsLastMoveTimestampDirty;
};

typedef std::shared_ptr<ClientProxy> ClientProxyPtr;

#endif /* defined(__noctisgames__ClientProxy__) */
