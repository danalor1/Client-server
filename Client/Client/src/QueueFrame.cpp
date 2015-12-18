/*
 * QueueFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */



#include "../include/QueueFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>




QueueFrame::QueueFrame(std::string cookie) {
	fcookie=cookie;
	 fmessage="";
	createFrame();
}

/**
 * returns the frames content
 */
std::string& QueueFrame::getFrameContent() {
	return fmessage;
}

/**
 *  adds to messages a Http frame and extracts the needed information from the input.
 */
void QueueFrame::createFrame() {

	std::string command = "GET /queue.jsp ";
	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
}

QueueFrame::~QueueFrame() {
}



