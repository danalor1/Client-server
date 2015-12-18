/*
 * CreateGroupFrame.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */


#include "../include/CreateGroupFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>



CreateGroupFrame::CreateGroupFrame()
		 {
	fmessage="";
}

CreateGroupFrame::CreateGroupFrame(std::string cookie,std::string message) {
	fcookie=cookie;
	 fmessage=message;
	createFrame();
}

/**
 * returns the frame content
 */
std::string& CreateGroupFrame::getFrameContent() {
	return fmessage;
}

/**
 *  adds to messages a Http frame and extracts the needed information from the input.
 */
void CreateGroupFrame::createFrame() {

	std::string command = "POST /create_group.jsp ";

	int index = fmessage.find(" ");
	std::string groupName = fmessage.substr(0, index);
				fmessage = fmessage.substr(index + 1);
	std::string users="";
	index=0;
	while(index>=0){
		index = fmessage.find(" ");
			std::string username = fmessage.substr(0, index);
			fmessage = fmessage.substr(index + 1);
			users.append(username);
			if(index>=0)
				users.append(", ");
	}
	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
	fmessage.append( "GroupName="+enc.url_encode(groupName)+"&");
	fmessage.append("Users="+enc.url_encode(users)+"\n");
}

CreateGroupFrame::~CreateGroupFrame() {
}



