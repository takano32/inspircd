#include "mode.h"
#include "channels.h"

class InspIRCd;

/** Channel mode +o
 */
class ModeChannelOp : public ModeHandler
{
 private:
 public:
	ModeChannelOp(InspIRCd* Instance);
	ModeAction OnModeChange(userrec* source, userrec* dest, chanrec* channel, std::string &parameter, bool adding);
	std::string AddOp(userrec *user,const char *dest,chanrec *chan,int status);
	std::string DelOp(userrec *user,const char *dest,chanrec *chan,int status);
	ModePair ModeSet(userrec* source, userrec* dest, chanrec* channel, const std::string &parameter);
	unsigned int GetPrefixRank();
	void RemoveMode(chanrec* channel);
	void RemoveMode(userrec* user);
};

