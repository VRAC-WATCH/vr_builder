//
//  sceneMgr.cpp
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

#include "sceneMgr.h"
//#include "scene.h" //uncomment when scene is available
//

//declarations



/*sceneMGR has instance of scene
only talking with builder, scene, and appMGR
look at functions in each - they tell the sceneMGR what to do
example: appMGR tells sceneMGR to build a block at a location.  sceneMGR takes info
and tells builder to create a block OSG node, then passes this node to the scene.*/

//definitions


void sceneManager::listenScene(std::string command)
{
    //"directions from the app manager" = command;
};

void sceneManager::sceneInstance(void)
{
 //   Scene instanceScene = new Scene();
}