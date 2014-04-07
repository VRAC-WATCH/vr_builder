//
//  XML.h
//
//  Created by Ken Kopecky on 6/9/12.
//  Updated by Trevor Richardson on 4/4/2014.
//

#ifndef XML_H
#define XML_H

#include "tinyxml.h"
#include <string>

namespace XML
{

	bool CICompare(std::string s1, std::string s2);			//case-insensitive string comparison

	void toUpper(std::string& s);
	
	//XML tools
	std::string xmlToString(TiXmlNode* n, bool deleteWhenDone = false);		//if dwd is true, the xml node will be deleted

	float stringToFloat(std::string s);
	bool stringToBool(std::string s);		//lots of strings can bool to yes or no...
	std::string floatToString(float f);

	//go through the node and get the value for the parameter called valName
	bool getValueFromNode(std::string valName, TiXmlNode* node, float& val);
	bool getValueFromNode(std::string valName, TiXmlNode* node, int& val);
	bool getValueFromNode(std::string valName, TiXmlNode* node, bool& val);
	bool getValueFromNode(std::string valName, TiXmlNode* node, std::string& value);
	bool recursiveXMLSearch(std::string valName, TiXmlNode* node, std::string& val); 
	
	//non-searching version of getValueFromNode
	bool readValue(TiXmlNode* node, bool& val);
	bool readValue(TiXmlNode* node, float& val);
	bool readValue(TiXmlNode* node, int& val);
//	bool readValue(TiXmlNode* node, QMath::Vec3& val); 
	bool readValue(TiXmlNode* node, std::string& val);
//	bool readValue(TiXmlNode* node, QMath::Vec4& val);
//	bool readValue(TiXmlNode* node, QMath::Matrix& val);

	TiXmlElement* makeElementWithNameAndValue(std::string name, float value);
	TiXmlElement* makeElementWithNameAndValue(std::string name, int value);
//	TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Vec3 value);
//	TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Vec4 value);
//	TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Matrix value);
//	TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Quat q);
	TiXmlElement* makeElementWithNameAndValue(std::string name, std::string value);
	TiXmlDocument* loadXmlFile(std::string name);	//reports errors and stuff
	
	std::string getLastErrorMessage();
}

#endif /** End XML_H. */