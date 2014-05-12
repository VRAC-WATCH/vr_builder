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
#include <vector>
/*Include Interaction header*/

class AppManager {
    
public:
    
    void pullData(void);
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
