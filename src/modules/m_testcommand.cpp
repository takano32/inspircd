#include <stdio.h>

#include "users.h"
#include "channels.h"
#include "modules.h"

/* $ModDesc: Povides a proof-of-concept test /WOOT command */

Server *Srv;
	 

void handle_woot(char **parameters, int pcnt, userrec *user)
{
	// this test command just accepts:
	// /woot :<text>
	// and sends <text> to all opers with +s mode.
	// NB: The ':' is *REQUIRED* otherwise the parser will
	// split the line into multiple parameters[]!
	//
	// If you want to process all the line with no leading colon, you must 
	// implement a parser here that assembles parameters[] to match the
	// syntax of your command - the way it is done in the core is to meet
	// rfc-compatibility.
	Srv->SendOpers(parameters[0]);
	

	// Here is a sample of how to send servermodes. Note that unless remote
	// servers in your net are u:lined, they may reverse this, but its a
	// quick and effective modehack.
	char* modes[3];
	modes[0] = "#chatspike";
	modes[1] = "+o";
	modes[2] = user->nick;
	
	// run the mode change, send numerics (such as "no such channel") back
	// to "user".
	Srv->SendMode(modes,3,user);
}

class ModuleTestCommand : public Module
{
 public:
	ModuleTestCommand()
	{
		Srv = new Server;
		// Create a new command:
		// command will be called /WOOT, and will
		// call handle_woot when triggered, the
		// 0 in the modes parameter signifies that
		// anyone can issue the command, and the
		// command takes only one parameter.
		Srv->AddCommand("WOOT",handle_woot,0,1);
	}
	
	virtual ~ModuleTestCommand()
	{
		delete Srv;
	}
	
	virtual Version GetVersion()
	{
		return Version(1,0,0,0);
	}
	
	virtual void OnUserConnect(userrec* user)
	{
	}

};


class ModuleTestCommandFactory : public ModuleFactory
{
 public:
	ModuleTestCommandFactory()
	{
	}
	
	~ModuleTestCommandFactory()
	{
	}
	
	virtual Module * CreateModule()
	{
		return new ModuleTestCommand;
	}
	
};


extern "C" void * init_module( void )
{
	return new ModuleTestCommandFactory;
}

