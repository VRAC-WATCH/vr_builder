/*
 *  Settings.cpp
 *  VeldtMonitor
 *
 *  Created by Kenneth Kopecky on 12/11/11.
 *  Copyright 2011 Orange Element Studios. All rights reserved.
 *
 */

#include "Settings.h"


TiXmlNode* gSettingsNode = NULL;
std::string gSettingsName;

namespace Settings
{
	bool loadFile(std::string name)
	{
		TiXmlDocument* d = XML::loadXmlFile(name);
		gSettingsName = name;
		if(!d)
		{
			gSettingsNode = new TiXmlElement("Settings");
			printf("failed to load the settings node\n");
			return false;
		}
		
		gSettingsNode = d->FirstChild();
		return true;
	}
	
	bool saveFile()
	{
		if(!gSettingsNode) return false;
		printf("saving settings as %s\n", gSettingsName.c_str());
		TiXmlDocument* dok = gSettingsNode->GetDocument();
		if(!dok)
		{
			dok = new TiXmlDocument;
			dok->LinkEndChild(gSettingsNode);
		}
		
		if(dok->SaveFile(gSettingsName) == false)
		{
			printf("Problem saving our settings file %s\n", gSettingsName.c_str());
		}
		
/*		for(TiXmlNode* n = gSettingsNode->FirstChild(); n; n = n->NextSibling())
		{
			printf("this setting is called %s\n", n->Value());
		}
*/		
		return true;
	}
	
	
	TiXmlNode*	__settingsNode()	{return gSettingsNode;}
		

}

