//
//  sceneMgr.cpp
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

#include "sceneMgr.h"
//#include "builder.h"
//include "SceneCommand.h"
//#include "scene.h" //uncomment when scene is available



//declarations


//These will eventually go in the .h, I'm just keeping them here for simplicity!
class sceneManager
{
    //private members
    
    //an instance of the scene (not really a string)
    std::string instanceScene;
    
    public:
    
    //reads in an input from the Application Manager
    void listenAppManger(const struct SceneCommand&);
    
    //sends an update from builder to the scene
    std::string builderToScene(void);//using strings for now
    
    //listens to the scene
    void listenScene( std::string );//using strings for now
    
    //An instance of some data from the scene
    void sceneInstance(void);
};

//Intended to store the location of the blocks in the scene in progress
//may end up moving somewhere else

class currentScene
{
    void storeBlock(const struct SceneCommand&);
};

//definitions

//commented temporarily

/*    void sceneManager::listenAppManger(const struct scenecommand&)
    {
        //SceneCommand scenecommand;
        //mModelGroup->addChild(Builder::instance().createBlock(scenecommand));
    };
*/

///////////////////
//I don't think builder will be passing info back to scenemanager, correct?

    /*std::string BuilderToScene(void)
    {
        //return "directions to the scene"
        return ("hello");
    };*/
///////////////////

    void sceneManager::listenScene(std::string command)
    {
        //"directions from the app manager" = command;
    };

    void sceneManager::sceneInstance(void)
    {
     //   Scene instanceScene = new Scene();
    }


    void currentScene::storeBlock(const struct scenecommand&)
    {
    
    };
