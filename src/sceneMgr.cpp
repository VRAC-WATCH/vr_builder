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

class sceneManager
{
    //private members
    
    //an instance of the scene (not really a string)
    std::string instanceScene;
    
    public:
    
    //reads in an input from the Application Manager
    void receiveAppManger(std::string);
    
    //sends an update from builder to the scene
    std::string builderToScene(void);//using strings for now
    
    //listens to the scene
    void listenScene( std::string );//using strings for now
    
    //An instance of some data from the scene
    void sceneInstance(void);
};


//definitions


    void sceneManager::receiveAppManger(std::string command)
    {
        //"directions from the app manager" = command;
    };

    std::string BuilderToScene(void)
    {
        //return "directions to the scene"
        return ("hello");
    };

    void sceneManager::listenScene(std::string command)
    {
        //"directions from the app manager" = command;
    };

    void sceneManager::sceneInstance(void)
    {
     //   Scene instanceScene = new Scene();
    }