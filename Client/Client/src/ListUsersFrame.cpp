/*
 * ListUsersFrame.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */


#include "../include/ListUsersFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>



ListUsersFrame::ListUsersFrame()
		 {
	fmessage="";
}

ListUsersFrame::ListUsersFrame(std::string cookie,std::string message) {
	fcookie=cookie;
	 fmessage=message;
	createFrame();
}

/**
 * returns the frame content
 */
std::string& ListUsersFrame::getFrameContent() {
	return fmessage;
}

/**
 *  adds to messages a Http frame and extracts the needed information from the input.
 */
void ListUsersFrame::createFrame() {

	std::string command = "POST /list.jsp ";

	unsigned int index = fmessage.find(" ");
	std::string listType;
	std::string GroupName;
	if(index>=fmessage.length())
	 listType=fmessage;
	else {
		listType=fmessage.substr(0,index);
		fmessage=fmessage.substr(index+1);
	if(listType.compare("Group")==0)
		GroupName=fmessage;
	}

	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
	fmessage.append("List Type="+enc.url_encode(listType));
	if(listType.compare("Group")==0)
		fmessage.append("&Group Name="+enc.url_encode(GroupName)+"\n");
	else fmessage.append("\n");

}

ListUsersFrame::~ListUsersFrame() {
}







