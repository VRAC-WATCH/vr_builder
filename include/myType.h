/*
 * myType.h
 * ASDS-viewer
 *
 * Created by Brandon Newendorp on 10/13/08.
 * Copyright 2008 Iowa State University. All rights reserved.
 *
 */


#ifndef __MYTYPE__
#define __MYTYPE__

#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>


struct myType
{
    bool drawBool;
    std::string message1;
	std::string message2;
	std::string message3;
	std::string message4;
	std::string message5;
	std::string message6;
	std::string message7;
	std::string message8;
	std::string message9;
	std::string message10;
	bool buttonFlag;
	std::string buttonEvent;
};


namespace vpr
{
    template<>
    inline void vpr::SerializableObjectMixin<myType>::writeObject(vpr::ObjectWriter *writer)
    { 
        writer->writeBool(drawBool);
        writer->writeString(message1);
		writer->writeString(message2);
		writer->writeString(message3);
		writer->writeString(message4);
		writer->writeString(message5);
		writer->writeString(message6);
		writer->writeString(message7);
		writer->writeString(message8);
		writer->writeString(message9);
		writer->writeString(message10);
		writer->writeBool(buttonFlag);
        writer->writeString(buttonEvent);
    }

    template<>
    inline void vpr::SerializableObjectMixin<myType>::readObject(vpr::ObjectReader *reader)
    {
        drawBool = reader->readBool();
        message1 = reader->readString();
		message2 = reader->readString();
		message3 = reader->readString();
		message4 = reader->readString();
		message5 = reader->readString();
		message6 = reader->readString();
		message7 = reader->readString();
		message8 = reader->readString();
		message9 = reader->readString();
		message10 = reader->readString();
		buttonFlag = reader->readBool();
        buttonEvent = reader->readString();
    }
}

#endif
