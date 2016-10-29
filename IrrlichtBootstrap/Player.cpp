#include "stdafx.h"
#include "Player.h"

Player::Player(ISceneNode * parent, ISceneManager * mgr, s32 id) : ISceneNode(parent, mgr, id)
{
	smgr = SceneManager;
	setPosition(parent->getPosition());
	setRotation(parent->getRotation());
}

void Player::OnRegisterSceneNode()
{
	if (IsVisible) SceneManager->registerNodeForRendering(this);
	ISceneNode::OnRegisterSceneNode();
}

void Player::Update(f32 deltaTime)
{ //from: http://irrlicht.sourceforge.net/forum/viewtopic.php?t=13339
	vector3df v = Parent->getPosition();
	vector3df r = Parent->getRotation();
	vector3df pos;
	m_speed = .1f;

	if (m_handler->IsKeyDown(KEY_KEY_W))
	{
		v.X = v.X + (float)((cos((r.Y - 90) * 3.14159265 / 180) * m_speed * deltaTime));
		v.Z = v.Z - (float)(sin((r.Y - 90) * 3.14159265 / 180) * m_speed * deltaTime);
	}
	if (m_handler->IsKeyDown(KEY_KEY_S))
	{
		v.X = v.X + (float)((cos((r.Y + 90) * 3.14159265 / 180) * m_speed * deltaTime));
		v.Z = v.Z - (float)(sin((r.Y + 90) * 3.14159265 / 180) * m_speed * deltaTime);
	}
	if (m_handler->IsKeyDown(KEY_KEY_D))
	{
		v.X = v.X + (float)((cos((r.Y) * 3.14159265 / 180) * m_speed * deltaTime));
		v.Z = v.Z - (float)(sin((r.Y) * 3.14159265 / 180) * m_speed * deltaTime);
	}
	if (m_handler->IsKeyDown(KEY_KEY_A))
	{
		v.X = v.X + (float)((cos((r.Y - 180) * 3.14159265 / 180) * m_speed * deltaTime));
		v.Z = v.Z - (float)(sin((r.Y - 180) * 3.14159265 / 180) * m_speed * deltaTime);
	}

	
	/*vector3df pos = Parent->getPosition();
	matrix4 mat = Parent->getAbsoluteTransformation();
	pos += vector3df(mat(0, 0) * m_speed * deltaTime,
		0,
		mat(2, 0) * m_speed * deltaTime);*/

	pos = v;

	getParent()->setPosition(pos);
	//setPosition(getPosition() + m_speed * deltaTime);
}

void Player::render()
{
}

