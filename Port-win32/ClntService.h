#ifndef CLNTSERVICE_H
#define CLNTSERVICE_H

#include "winservice.h"

class TClntService : public TWinService
{
public:
	TClntService(void);
	void Run();
    void OnStop();
    void OnShutdown();
	void Install();
	void Uninstall();
	~TClntService(void);
    int ParseStandardArgs(int argc,char* argv[]);

	
};

#endif
