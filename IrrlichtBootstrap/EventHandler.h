#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Common.h"

class EventHandler : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event);

	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	EventHandler();
	~EventHandler();

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif
