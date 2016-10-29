#include "stdafx.h"
#include "CollisionHandler.h"


CollisionHandler::CollisionHandler()
{
}


CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::CalculateSceneCollisions(scene::ISceneManager* scenemgr, scene::IMetaTriangleSelector* metaSelector, ICameraSceneNode* cam)
{
	//
	// the following if is basically the same as ISceneNode_assignTriangleSelector
	//
	core::list<ISceneNode*> nodes = scenemgr->getRootSceneNode()->getChildren();

	for (ISceneNode* current : nodes)
	{
		printf("Node name is: %s \n", current->getName());
		printf("Node id is: %d \n", current->getID());
		printf("Node type:");
		//  printf ("Node type: %s=",smgr->getSceneNodeTypeName());
		if (current->getType() == ESNT_UNKNOWN) printf("Unknown mesh type \n\n");
		if (current->getType() == ESNT_MESH)
		{
			printf("Standard Mesh \n\n");
			IMeshSceneNode* nodeMesh = (IMeshSceneNode*)current;
			IMesh* mesh = nodeMesh->getMesh();

			ITriangleSelector* selector;
			selector = scenemgr->createOctreeTriangleSelector(mesh, current, 128);
			current->setTriangleSelector(selector);
			metaSelector->addTriangleSelector(selector);
			selector->drop();
			//set fog!!!
			nodeMesh->setMaterialFlag(EMF_FOG_ENABLE, true);
			//disable mipmaps
			for (int i = 0; i < nodeMesh->getMaterialCount(); i++)
			{
				nodeMesh->getMaterial(i).UseMipMaps = false;
			}
		}
		if (current->getType() == ESNT_ANIMATED_MESH) printf("Animated Mesh! \n\n");
		if (current->getType() == ESNT_SKY_BOX) printf("SkyBox! \n\n");
		if (current->getType() == ESNT_CAMERA_FPS) printf("Fps Camera! \n\n");
		if (current->getType() == ESNT_CAMERA_MAYA) printf("Maya Camera! \n\n");
		if (current->getType() == ESNT_CAMERA)
		{
			printf("STD Camera! \n");
			printf("The current position of this camera is: %f,%f,%f\n\n", current->getPosition().X, current->getPosition().Y, current->getPosition().Z);
			if (cam != NULL)
				cam->setPosition(current->getPosition());
			else
				printf("Camera not found...\n");
		}
		if (current->getType() == ESNT_PARTICLE_SYSTEM) printf("Particles! \n\n");
		if (current->getType() == ESNT_LIGHT) printf("Light! \n\n");
		if (current->getType() == ESNT_OCTREE)
		{
			// Occ Trees are for land
			printf("Occtree! \n");
			io::IAttributes* attribs = intro->getFileSystem()->createEmptyAttributes();
			if (attribs)
			{// get the mesh name out 
				current->serializeAttributes(attribs);
				core::stringc name = attribs->getAttributeAsString("Mesh");
				attribs->drop();
				// get the animated mesh for the object 
				scene::IAnimatedMesh* mesh = smgr->getMesh(name.c_str());
				if (mesh)
				{
					scene::ITriangleSelector* selector =
						smgr->createOctreeTriangleSelector(mesh->getMesh(0), current, 128);
					current->setTriangleSelector(selector);
					metaSelector->addTriangleSelector(selector);
					selector->drop();
				}

			}
		}
	}

	printf("DONE ALL!\n");
}