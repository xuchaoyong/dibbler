#ifndef IAADDRESS_H
#define IAADDRESS_H

#include "SmartPtr.h"
#include "Container.h"
#include "Opt.h"
#include "IPv6Addr.h"

class TOptIAAddress : public TOpt
{
  public:
    TOptIAAddress( char * &addr, int &n, TMsg* parent);
    TOptIAAddress( SmartPtr<TIPv6Addr> addr, long pref, long valid, TMsg* parent);
    int getSize();
    
    char * storeSelf( char* buf);
    SmartPtr<TIPv6Addr> getAddr();
    unsigned long getPref();
    unsigned long getValid();
    bool isValid();    
 private:
    SmartPtr<TIPv6Addr> Addr;
    unsigned long Valid;
    unsigned long Pref;
    bool ValidOpt;
};

#endif
