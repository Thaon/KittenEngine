#include "stdafx.h"
#include "EventHandler.h"


EventHandler::EventHandler()
{
	memset(KeyIsDown, false, sizeof(KeyIsDown));
}


EventHandler::~EventHandler()
{
}

bool EventHandler::OnEvent(const SEvent & event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		{
			if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
				switch (event.KeyInput.Key)
				{
				case KEY_ESCAPE:

					break;
				}
			return true;
		}
	}
	return false;
}