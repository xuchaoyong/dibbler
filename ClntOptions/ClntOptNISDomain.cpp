/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 *
 * released under GNU GPL v2 or later licence
 *
 * $Id: ClntOptNISDomain.cpp,v 1.3 2007-01-07 20:18:45 thomson Exp $
 *
 */

#include "ClntOptNISDomain.h"
#include "ClntOptServerIdentifier.h"
#include "Portable.h"
#include "ClntMsg.h"
#include "Logger.h"

TClntOptNISDomain::TClntOptNISDomain(string domain, TMsg* parent)    
    :TOptString(OPTION_NIS_DOMAIN_NAME, domain, parent) {
}

TClntOptNISDomain::TClntOptNISDomain(char *buf, int bufsize, TMsg* parent)
    :TOptString(OPTION_NIS_DOMAIN_NAME, buf,bufsize, parent) {
}

bool TClntOptNISDomain::doDuties() {
    string reason = "trying to set NIS domain.";
    int ifindex = this->Parent->getIface();
    SmartPtr<TIPv6Addr> addr = this->Parent->getAddr();
    TClntMsg * msg = (TClntMsg*)(this->Parent);
    SmartPtr<TClntIfaceMgr> ifaceMgr = msg->getClntIfaceMgr();
    if (!ifaceMgr) {
	Log(Error) << "Unable to access IfaceMgr while " << reason << LogEnd;
        return false;
    }
    SmartPtr<TClntIfaceIface> iface = (Ptr*)ifaceMgr->getIfaceByID(ifindex);
    if (!iface) {
	Log(Error) << "Unable to find interface with ifindex=" << ifindex 
		   << " while " << reason << LogEnd;
        return false;
    }

    if (!this->DUID) {
	Log(Error) << "Unable to find proper DUID while " << reason << LogEnd;
	return false;
    }

    SmartPtr<TClntCfgMgr> cfgMgr = msg->getClntCfgMgr();
    SmartPtr<TClntCfgIface> cfgIface = cfgMgr->getIface(ifindex);
    cfgIface->setNISDomainState(STATE_CONFIGURED);

    return iface->setNISDomain(this->DUID, addr,this->Str);
}

void TClntOptNISDomain::setSrvDuid(SmartPtr<TDUID> duid) {
    this->SrvDUID=duid;
}
