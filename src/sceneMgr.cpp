//
//  sceneMgr.cpp
//  VRBuilder
//
//  Created by Frederick Thompson on 4/25/14.
//
//

#include "sceneMgr.h"
//#include "builder.h"
#include "SceneCommand.h"
//#include "scene.h" //uncomment when scene is available

    
    //an instance of the scene (not really a string)
    std::string instanceScene;
    
    //reads in an input from the Application Manager
    void sceneManager::listenAppManger(const SceneCommand scenecommand&)
    {
    //SceneCommand scenecommand;
    //mModelGroup->addChild(Builder::instance().createBlock(scenecommand));
    }


    void sceneManager::listenScene(std::string command)
    {
        //"directions from the app manager" = command;
    }

    void sceneManager::sceneInstance(void)
    {
     //   Scene instanceScene = new Scene();
    }


    void currentScene::storeBlock(const struct scenecommand&)
    {
    
    };
