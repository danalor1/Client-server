/*
 * LogoutFrame.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */



#include "../include/LogoutFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>




LogoutFrame::LogoutFrame(std::string cookie) {
	fcookie=cookie;
	 fmessage="";
	createFrame();
}

/**
 * returns the frame content
 */
std::string& LogoutFrame::getFrameContent() {
	return fmessage;
}

/**
 * converts message to http format.
 */
void LogoutFrame::createFrame() {

	std::string command = "GET /logout.jsp ";
	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
}

LogoutFrame::~LogoutFrame() {
}



