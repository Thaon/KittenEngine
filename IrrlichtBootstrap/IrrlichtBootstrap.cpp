// IrrlichtBootstrap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common.h"
#include "EventHandler.h"
#include "CollisionHandler.h"
#include "Player.h"

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};

int main()
{
	EventHandler handler;
	IrrlichtDevice *device =
		createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false , false, false, &handler);

	if (!device)
		return 1;

	device->setWindowCaption(L"Irrlicht bootstrap");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IMetaTriangleSelector* metaSelector;
	ISceneNodeAnimatorCollisionResponse* anim;
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	//hide the mouse
	device->getCursorControl()->setVisible(false);

	//set up game here
	smgr->loadScene(L"lmap.irr");
	smgr->setLightManager(0);

	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 50, 0.1f, -1, 0, 0, true, 0.5f, false, true);
	ILightSceneNode* pointLight = smgr->addLightSceneNode(0, vector3df(0, 0, 0), SColor(255, 255, 255, 255), 100, -1);
	
	Player* player = new Player(camera, smgr, 0);
	player->SetHandler(&handler);
	player->setPosition(vector3df(0,0,0));
	player->addChild(pointLight);
	pointLight->setPosition(player->getPosition());

	//setting the collision layers here
	CollisionHandler collHandler;
	metaSelector = smgr->createMetaTriangleSelector();
	collHandler.CalculateSceneCollisions(smgr, metaSelector, camera);

	//enable fog
	driver->setFog(video::SColor(255, 0, 0, 0), video::EFT_FOG_LINEAR, 100, 200, .5f, true, true);
	

	//player stuff here
	//camera->setPosition(smgr->getSceneNodeFromName("Camera1")->getPosition());

	// DEfine the collision reponse for the FPS Camera
	anim = smgr->createCollisionResponseAnimator(metaSelector, camera, core::vector3df(10, 26, 10),
	//metaSelector, camera, core::vector3df(10,26,10),
	core::vector3df(0, -1.0f, 0),
	core::vector3df(0, 24, 0));

	camera->addAnimator(anim);
	anim->drop();
	metaSelector->drop();

	
	//game loop
	bool isRunning = true;
	f32 now;
	f32 then = device->getTimer()->getTime();
	f32 deltaTime;
	
	while (device->run() && isRunning)
	{
		now = device->getTimer()->getTime();
		deltaTime = now - then;
		then = now;
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		//input
		if (handler.IsKeyDown(KEY_ESCAPE))
		{
			isRunning = false;
		}

		//update player
		player->Update(deltaTime);

		//draw
		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	//clean up
	device->drop();

    return 0;
}

