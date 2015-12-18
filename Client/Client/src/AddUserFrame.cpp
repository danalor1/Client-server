/*
 * AddUserFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */





#include "../include/AddUserFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>



AddUserFrame::AddUserFrame()
		 {
	fmessage="";
}

AddUserFrame::AddUserFrame(std::string cookie,std::string message) {
	fcookie=cookie;
	 fmessage=message;
	createFrame();
}

/**
 * returns the frame content
 */
std::string& AddUserFrame::getFrameContent() {
	return fmessage;
}

/**
 * adds to messages a Http frame and extracts the needed information from the input.
 */
void AddUserFrame::createFrame() {

	std::string command = "POST /add_user.jsp ";
	int index = fmessage.find(" ");
	std::string target = fmessage.substr(0, index);
	fmessage = fmessage.substr(index + 1);
	std::string phone;
		if(index>=0)
		 phone = fmessage;
		else phone=" ";
	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
	fmessage.append("Target=" + enc.url_encode(target) + "&");
	fmessage.append("User=" + enc.url_encode(phone) + "\n");
}

AddUserFrame::~AddUserFrame() {
}
