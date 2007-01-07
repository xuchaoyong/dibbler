/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 *
 * released under GNU GPL v2 or later licence
 *
 * $Id: ClntOptSIPDomain.cpp,v 1.3 2007-01-07 20:18:46 thomson Exp $
 *
 */

#include "ClntOptSIPDomain.h"
#include "ClntOptServerIdentifier.h"
#include "Portable.h"
#include "ClntMsg.h"
#include "Logger.h"

TClntOptSIPDomain::TClntOptSIPDomain(List(string) *domains, TMsg* parent)    
    :TOptStringLst(OPTION_SIP_DOMAINS, *domains, parent) {
}

TClntOptSIPDomain::TClntOptSIPDomain(char *buf, int bufsize, TMsg* parent)
    :TOptStringLst(OPTION_SIP_DOMAINS, buf,bufsize, parent) {
}

bool TClntOptSIPDomain::doDuties() {
    string reason = "trying to set SIP domain(s).";
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
    cfgIface->setSIPDomainState(STATE_CONFIGURED);

    return iface->setSIPDomainLst(this->DUID, addr,this->StringLst);
}

void TClntOptSIPDomain::setSrvDuid(SmartPtr<TDUID> duid) {
    this->SrvDUID=duid;
}
