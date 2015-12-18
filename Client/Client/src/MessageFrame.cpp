/*
 * MessageFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#include "../include/MessageFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>


MessageFrame::MessageFrame()
		 {
	fmessage="";
	createFrame();
}
MessageFrame::MessageFrame(std::string response)
		 {
	fmessage=response;
	createFrame();
}

/**
 * returns the frame content
 */
std::string& MessageFrame::getFrameContent() {
	return fmessage;
}

/**
 * extracts the message from the response
 */
void MessageFrame::createFrame() {
	int index=fmessage.find("$");
	fmessage = fmessage.substr(0,index-1);
}

MessageFrame::~MessageFrame() {
}
