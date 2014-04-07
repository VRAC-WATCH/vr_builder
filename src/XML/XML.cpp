//
//  XML.cpp
//
//  Created by Ken Kopecky on 6/9/12.
//	Updated by Trevor Richardson on 4/4/2014.
//

#include "XML.h"

namespace XML
{

std::string gLastErrorMessage;

bool CICompare(std::string s1, std::string s2)
{
	if(s1.length() != s2.length()) return false;
	toUpper(s1);
	toUpper(s2);
	return (s1 == s2);
}


void toUpper(std::string& s)
{
	for (size_t i=0; i<s.size(); i++)
	{
		if (isalpha(s[i]) && !isupper(s[i]))
			s[i] = s[i] - 'a' + 'A';
	}
}

bool readValue(TiXmlNode* node, float& val)
{
	if(node->FirstChild())
	{ 
		val = stringToFloat(node->FirstChild()->Value());		//got it!
		return true;
	}
	return false;
}
bool readValue(TiXmlNode* node, bool& val)
{
	if(node->FirstChild())
	{ 
		val = stringToBool(node->FirstChild()->Value());		//got it!
		return true;
	}
	return false;
}

bool readValue(TiXmlNode* node, int& val)
{
	if(node->FirstChild())
	{ 
		val = (int)stringToFloat(node->FirstChild()->Value());		//got it!
		return true;
	}
	return false;
}

bool readValue(TiXmlNode* node, std::string& val)
{
	if(node->FirstChild())
	{ 
		val = node->FirstChild()->Value();		//got it!
		return true;
	}
	val = "";
	return false;
}



//some helper functions for accessing the XML
float stringToFloat(std::string s)
{
	float f=-1;
	sscanf(s.c_str(), "%f", &f);
	return f;

}

std::string intToString(int f)
{
	char text[48];
	sprintf(text, "%i", f);
	//remove trailing zeros.  they just make our XML file bigger and uglier
	return std::string(text);
}


int stringToInt(std::string s)
{
	int f=-1;
	sscanf(s.c_str(), "%i", &f);
	return f;

}


bool stringToBool(std::string s)
{
	float val = stringToFloat(s);
	if(val == 0) return false;
	if(val != -1) return true;
	if(CICompare(s, "yes")) return true;
	if(CICompare(s, "true")) return true;
	if(CICompare(s, "si")) return true;
	if(CICompare(s, "ja")) return true;
	if(CICompare(s, "yup")) return true;
	if(CICompare(s, "yeah")) return true;
	if(CICompare(s, "affirmative")) return true;
	return false;
}

std::string xmlToString(TiXmlNode* n, bool deleteWhenDone)
{
	TiXmlPrinter p;
	n->Accept(&p);
	std::string x = p.Str();
	if(deleteWhenDone) delete n;
	return x;
	TiXmlDocument doc;
	doc.InsertEndChild(*n);

	std::string stringOut;
	stringOut << doc;
	return stringOut;
	return "";

}

/*
TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Quat q)
{
	TiXmlElement* boppa = new TiXmlElement(name);
	boppa->LinkEndChild(makeElementWithNameAndValue("x", q.x));
	boppa->LinkEndChild(makeElementWithNameAndValue("y", q.y));
	boppa->LinkEndChild(makeElementWithNameAndValue("z", q.z));
	boppa->LinkEndChild(makeElementWithNameAndValue("w", q.w));
	return boppa;
}

TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Vec3 q)
{
	TiXmlElement* boppa = new TiXmlElement(name);
	boppa->LinkEndChild(makeElementWithNameAndValue("x", q.x));
	boppa->LinkEndChild(makeElementWithNameAndValue("y", q.y));
	boppa->LinkEndChild(makeElementWithNameAndValue("z", q.z));
	return boppa;
}


TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Vec4 q)
{
	TiXmlElement* boppa = new TiXmlElement(name);
	boppa->LinkEndChild(makeElementWithNameAndValue("r", q.x));
	boppa->LinkEndChild(makeElementWithNameAndValue("g", q.y));
	boppa->LinkEndChild(makeElementWithNameAndValue("b", q.z));
	boppa->LinkEndChild(makeElementWithNameAndValue("a", q.w));
	return boppa;
}

TiXmlElement* makeElementWithNameAndValue(std::string name, QMath::Matrix q)
{
	TiXmlElement* boppa = new TiXmlElement(name);
	int i = 0;
	boppa->LinkEndChild(makeElementWithNameAndValue("1", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("2", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("3", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("4", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("5", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("6", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("7", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("8", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("9", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("10", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("11", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("12", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("13", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("14", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("15", q.m[i++]));
	boppa->LinkEndChild(makeElementWithNameAndValue("16", q.m[i++]));
	return boppa;
}
*/

TiXmlElement* makeElementWithNameAndValue(std::string name, float value)
{
	TiXmlElement* boppa = new TiXmlElement(name.c_str());
	boppa->LinkEndChild(new TiXmlText(floatToString(value).c_str()));
	return boppa;
}


TiXmlElement* makeElementWithNameAndValue(std::string name, int value)
{
	TiXmlElement* boppa = new TiXmlElement(name.c_str());
	boppa->LinkEndChild(new TiXmlText(intToString(value).c_str()));
	return boppa;
}

TiXmlElement* makeElementWithNameAndValue(std::string name, std::string value)
{
	TiXmlElement* boppa = new TiXmlElement(name.c_str());
	boppa->LinkEndChild(new TiXmlText((value).c_str()));
	return boppa;
}

std::string floatToString(float f)
{
	char text[48];
	int length = sprintf(text, "%f", f);
	//remove trailing zeros.  they just make our XML file bigger and uglier
	while(text[length-1] == '0' && length)
		text[--length] = 0;
	//remove a trailing decimal as well
	if(text[length-1] == '.')
		text[length-1] = 0;
	return std::string(text);
}

TiXmlDocument* loadXmlFile(std::string fileName)
{
//	fileName = getFilePath(fileName, true);
	TiXmlDocument* doc = new TiXmlDocument;
	bool found = doc->LoadFile((fileName).c_str(), TIXML_ENCODING_UTF8);
	if(!found)
	{
		char em[4096];
		sprintf(em, "Unable to load XML file %s\n  The error reported was:\n%s\nat row %i, column %i\n",
			fileName.c_str(), doc->ErrorDesc(), doc->ErrorRow(), doc->ErrorCol());
		printf("%s\n", em);
		gLastErrorMessage = em;
		delete doc;
		return NULL;
	}
	gLastErrorMessage = "No Error";

	return doc;

}

std::string getLastErrorMessage()	{return gLastErrorMessage;}
/*bool readValue(TiXmlNode* node, QMath::Vec4& q)
{

	bool r = getValueFromNode("r", node, q.x);
	bool g= getValueFromNode("g", node, q.y);
	bool b = getValueFromNode("b", node, q.z);	
	bool a = getValueFromNode("a", node, q.w);
//	printf("%i %i %i %i\n", r, g, b, a);
	return r*g*b*a;
}

bool readValue(TiXmlNode* node, QMath::Matrix& q)
{
	bool worked = true;
	int i = 0;

	worked = worked && getValueFromNode("1", node, q.m[i++]);
	worked = worked && getValueFromNode("2", node, q.m[i++]);
	worked = worked && getValueFromNode("3", node, q.m[i++]);//	printf("%i %i %i %i\n", r, g, b, a);
	worked = worked && getValueFromNode("4", node, q.m[i++]);
	worked = worked && getValueFromNode("5", node, q.m[i++]);
	worked = worked && getValueFromNode("6", node, q.m[i++]);
	worked = worked && getValueFromNode("7", node, q.m[i++]);
	worked = worked && getValueFromNode("8", node, q.m[i++]);
	worked = worked && getValueFromNode("9", node, q.m[i++]);
	worked = worked && getValueFromNode("10", node, q.m[i++]);
	worked = worked && getValueFromNode("11", node, q.m[i++]);
	worked = worked && getValueFromNode("12", node, q.m[i++]);
	worked = worked && getValueFromNode("13", node, q.m[i++]);
	worked = worked && getValueFromNode("14", node, q.m[i++]);
	worked = worked && getValueFromNode("15", node, q.m[i++]);
	worked = worked && getValueFromNode("16", node, q.m[i++]);
	return worked;
}



bool readValue(TiXmlNode* node, QMath::Vec3& q)
{

	bool r = getValueFromNode("x", node, q.v[0]);
	bool g= getValueFromNode("y", node, q.v[1]);
	bool b = getValueFromNode("z", node, q.v[2]);	
//	printf("%i %i %i %i\n", r, g, b, a);
	return r*g*b;
}

*/
//go through the node and get the value for the parameter called valName
bool getValueFromNode(std::string valName, TiXmlNode* node, float& val)
{
	TiXmlNode* pChild;

	//go through all the subnodes and find a text node with the value we want
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
//		printf("this value:  %s\n", pChild->Value());
		if(CICompare(pChild->Value(), valName))
		{
			TiXmlNode* valChild = pChild->FirstChild();
			
			if(valChild)		//got it!
			{
				val = stringToFloat(valChild->Value());
				return true;
			}
		}
	}

	 return false;
}


bool getValueFromNode(std::string valName, TiXmlNode* node, int& val)
{
	TiXmlNode* pChild;

	//go through all the subnodes and find a text node with the value we want
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
//		printf("this value:  %s\n", pChild->Value());
		if(CICompare(pChild->Value(), valName))
		{
			TiXmlNode* valChild = pChild->FirstChild();
			
			if(valChild)		//got it!
			{
				val = stringToInt(valChild->Value());
				return true;
			}
		}
	}

	 return false;
}

bool getValueFromNode(std::string valName, TiXmlNode* node, bool& val)
{
	TiXmlNode* pChild;

	//go through all the subnodes and find a text node with the value we want
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
//		printf("this value:  %s\n", pChild->Value());
		if(CICompare(pChild->Value(), valName))
		{
			TiXmlNode* valChild = pChild->FirstChild();
			
			if(valChild)		//got it!
			{
				val = stringToBool(valChild->Value());
				return true;
			}
		}
	}

	 return false;
}

//go through the node and get the value for the parameter called valName
bool getValueFromNode(std::string valName, TiXmlNode* node, std::string& val)
{
	TiXmlNode* pChild;

	//go through all the subnodes and find a text node with the value we want
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
//		printf("this value:  %s.  we want %s\n", pChild->Value(), valName.c_str());
		if(CICompare(pChild->Value(), valName))
		{
			TiXmlNode* valChild = pChild->FirstChild();
			
			if(valChild)		//got it!
			{
				val = valChild->Value();
				return true;
			}
		}
	}

	 return false;
}


bool recursiveXMLSearch(std::string valName, TiXmlNode* node, std::string& val)
{
	if(!node) return false;
//	printf("searching for %s in node %s\n", valName.c_str(), node->Value());
	for(TiXmlNode* n = node->FirstChild(); n; n = n->NextSibling())
	{
		
		if(n->ToText())
			continue;		//don't search actual data
//		printf("search child %s\n", n->Value());
		if(CICompare(n->Value(), valName))
		{
			readValue(n, val);
			return true;
		}
		
		if(recursiveXMLSearch(valName, n, val))
			return true;
	}
	
	return false;
}

}