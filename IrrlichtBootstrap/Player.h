//THIS WILL GET REFACTORED INTO GAMEOBJECT
#pragma once

#include "Common.h"
#include "EventHandler.h"

class Player : public ISceneNode
{
public:
	Player(ISceneNode* parent, ISceneManager* mgr, s32 id);

	void SetHandler(EventHandler* handler) { m_handler = handler; }
	void SetCamera(ISceneNode* cam) { m_camera = cam; }

	virtual void OnRegisterSceneNode();
	void Update(f32 deltaTime);
	virtual void render();
	virtual const core::aabbox3d<f32>& getBoundingBox() const { return m_bbox; }

private:
	ISceneManager* smgr;
	EventHandler* m_handler;
	f32 m_speed;
	aabbox3d<f32> m_bbox;
	ISceneNode* m_camera;
};

