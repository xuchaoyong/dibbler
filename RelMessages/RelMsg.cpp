/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 *
 * released under GNU GPL v2 or later licence
 *
 * $Id: RelMsg.cpp,v 1.1 2005-01-11 22:53:35 thomson Exp $
 *
 * $Log: not supported by cvs2svn $
 *
 */

#ifdef WIN32
#include <winsock2.h>
#endif
#ifdef LINUX
#include <netinet/in.h>
#endif 

#include "Logger.h"
#include "RelMsg.h"

// --- options ---
#include "RelOptInterfaceID.h"
#include "RelOptRelayMsg.h"
#include "RelOptGeneric.h"

//Constructor builds message on the basis of received message
TRelMsg::TRelMsg(TCtx ctx, int iface,  SmartPtr<TIPv6Addr> addr, char* data,  int dataLen)
    :TMsg(iface, addr, data, dataLen) {
    // data+=4, dataLen-=4 is modified in TMsg
    if (dataLen<=0) // avoid decoding of empty messages.
	return;

    int pos=0;
    while (pos<dataLen)	{
        short code = ntohs( * ((short*) (data+pos)));
        pos+=2;
        short length = ntohs(*((short*)(data+pos)));
        pos+=2;
        SmartPtr<TOpt> ptr;

	if (!allowOptInMsg(this->MsgType,code)) {
	    Log(Warning) << "Option " << code << " not allowed in message type="<< MsgType <<". Ignoring." << LogEnd;
	    pos+=length;
	    continue;
	}
	if (!allowOptInOpt(this->MsgType,0,code)) {
	    Log(Warning) <<"Option " << code << " can't be present in message (type="
			 << MsgType <<") directly. Ignoring." << LogEnd;
	    pos+=length;
	    continue;
	}

	ptr= 0;
	switch (code) {
	case OPTION_RELAY_MSG:
	    ptr = new TRelOptRelayMsg(data+pos,length,this);
	    break;
	case OPTION_INTERFACE_ID:
	    ptr = new TRelOptInterfaceID(data+pos,length,this);
	    break;
	default:
	    ptr = new TRelOptGeneric(data+pos, length, this);
	    break;
	}

	if ( (ptr) && (ptr->isValid()) )
	    Options.append( ptr );
	else
	    Log(Warning) << "Option " << code << " is invalid. Option ignored." << LogEnd;
        pos+=length;
    }

}