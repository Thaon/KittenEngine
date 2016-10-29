#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Common.h"

class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	void CalculateSceneCollisions(scene::ISceneManager* scenemgr, scene::IMetaTriangleSelector* meta, ICameraSceneNode* cam);

private:
	//parse irr to octree
	IrrlichtDevice *intro = 0;
	IVideoDriver* driver = 0;
	ISceneManager* smgr;
	IMetaTriangleSelector* metaSelector;
	ISceneNodeAnimatorCollisionResponse* anim;
	ICameraSceneNode* camera = NULL;
};

#endif
