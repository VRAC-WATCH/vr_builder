//
//  AppManager.h
//  
//
//  Created by Adam Kohl on 4/23/14.
//
//

#ifndef ____AppManager__
#define ____AppManager__

#include "InteractionManager.h"
/*Include Ui Header header*/

class AppManager {
    
public:
    
    /* pullData retreives the necessary data from the Interaction Manager and UiViewer*/
    
    void pullData(void);
    
    /*pushData sends data to update the scene manager*/
    
    void pushData(void);

protected:
    
    AppManager();
    ~AppManager();
    
private:
    
    InteractionManager*    _interactionManager;
    //UiViewer*       _uiViewer;
    
    //std::vector</*type*/>   _pulledData;
    //std::vector</*type*/>   _interactionData;
    //std::vector</*type*/>   _uiViewerData;

};

#endif /* defined(____AppManager__) */
