/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 * changes: Krzysztof Wnuk
 *
 * released under GNU GPL v2 or later licence
 *
 * $Id: SrvCfgIface.h,v 1.23 2006-12-31 11:46:09 thomson Exp $
 *
 */

class TSrvCfgIface;
#ifndef SRVCONFIFACE_H
#define SRVCONFIFACE_H
#include "DHCPConst.h"
#include "SrvCfgAddrClass.h"
#include "SrvCfgTA.h"
#include "SrvCfgPD.h"
#include "SrvParsGlobalOpt.h"
#include <iostream>
#include <string>
#include "SrvOptVendorSpec.h"
#include "SrvCfgOptions.h"

using namespace std;

class TSrvCfgIface: public TSrvCfgOptions
{
    friend ostream& operator<<(ostream& out,TSrvCfgIface& iface);
public:
    TSrvCfgIface();
    TSrvCfgIface(string ifaceName);
    TSrvCfgIface(int ifaceNr);
    virtual ~TSrvCfgIface();
    void setDefaults();

    void setName(string ifaceName);
    void setID(int ifaceID);
    int	getID();
    string getName();
    string getFullName();

    // permanent address management (IA_NA)
    void addAddrClass(SmartPtr<TSrvCfgAddrClass> addrClass);
    void firstAddrClass();
    bool getPreferedAddrClassID(SmartPtr<TDUID> duid, SmartPtr<TIPv6Addr> clntAddr, unsigned long &classid);
    bool getAllowedAddrClassID(SmartPtr<TDUID> duid, SmartPtr<TIPv6Addr> clntAddr, unsigned long &classid);
    SmartPtr<TSrvCfgAddrClass> getAddrClass();
    SmartPtr<TSrvCfgAddrClass> getClassByID(unsigned long id);
    SmartPtr<TSrvCfgAddrClass> getRandomClass(SmartPtr<TDUID> clntDuid, SmartPtr<TIPv6Addr> clntAddr);
    long countAddrClass();

    // temporary address management (IA_TA)
    void addTA(SmartPtr<TSrvCfgTA> ta);
    void firstTA();
    SmartPtr<TSrvCfgTA> getTA();
    SmartPtr<TSrvCfgTA> getTA(SmartPtr<TDUID> duid, SmartPtr<TIPv6Addr> clntAddr);

    // prefix management (IA_PD)
    void addPDClass(SmartPtr<TSrvCfgPD> PDClass);
    SmartPtr<TSrvCfgPD> getPDByID(unsigned long id);
    SmartPtr<TSrvCfgPD> getRandomPrefix(SmartPtr<TDUID> clntDuid, SmartPtr<TIPv6Addr> clntAddr);
    long countPD();
    void addPD(SmartPtr<TSrvCfgPD> pd);
    void firstPD();
    SmartPtr<TSrvCfgPD> getPD();

    // other
    SmartPtr<TIPv6Addr> getUnicast();
    void setNoConfig();
    void setOptions(SmartPtr<TSrvParsGlobalOpt> opt);
    
    unsigned char getPreference();

    bool getRapidCommit();

    long getIfaceMaxLease();
    unsigned long getClntMaxLease();

    // IA address functions
    void addClntAddr(SmartPtr<TIPv6Addr> ptrAddr);
    void delClntAddr(SmartPtr<TIPv6Addr> ptrAddr);

    // TA address functions
    void addTAAddr();
    void delTAAddr();

    // PD prefixes functions
    void addClntPrefix(SmartPtr<TIPv6Addr> ptrPD);
    void delClntPrefix(SmartPtr<TIPv6Addr> ptrPD);
    bool supportPrefixDelegation();

    // relays
    string getRelayName();
    int getRelayID();
    int getRelayInterfaceID();
    bool isRelay();
    void setRelayName(string name);
    void setRelayID(int id);

    // options


    // option: FQDN
    List(TFQDN) * getFQDNLst();
    SPtr<TFQDN> getFQDNName(SmartPtr<TDUID> duid, SmartPtr<TIPv6Addr> addr, string hint);
    SmartPtr<TDUID> getFQDNDuid(string name);
    void setFQDNLst(List(TFQDN) * fqdn);
    int getFQDNMode();
    string getFQDNModeString();
    int  getRevDNSZoneRootLength();
    void setRevDNSZoneRootLength(int revDNSZoneRootLength);
    void setFQDNMode(int FQDNMode);
    bool supportFQDN();

private:
    unsigned char preference;
    int	ID;
    string Name;
    bool NoConfig;
    SmartPtr<TIPv6Addr> Unicast;
    unsigned long IfaceMaxLease;
    unsigned long ClntMaxLease;
    bool RapidCommit;	
    List(TSrvCfgAddrClass) SrvCfgAddrClassLst; // IA_NA list (normal addresses)

    // --- Temporary Addresses ---
    List(TSrvCfgTA) SrvCfgTALst; // IA_TA list (temporary addresses)

    // --- Prefix Delegation ---
    List(TSrvCfgPD) SrvCfgPDLst;
    bool PrefixDelegationSupport;

    // --- relay ---
    bool Relay;
    string RelayName;     // name of the underlaying physical interface (or other relay)
    int RelayID;          // ifindex
    int RelayInterfaceID; // value of interface-id option (optional)

    // --- option: FQDN ---
    List(TFQDN) FQDNLst;
    int FQDNMode;
    int revDNSZoneRootLength;
    unsigned int PrefixLength;
    bool FQDNSupport;
};

#endif /* SRVCONFIFACE_H */
