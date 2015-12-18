/*
 * LoginFrame.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */



#include "../include/LoginFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>



LoginFrame::LoginFrame()
		 {
	fmessage="";
}

LoginFrame::LoginFrame(std::string message) {
	 fmessage=message;
	 enc=Encoder();
	createFrame();
}

/**
 * returns the frame content
 */
std::string& LoginFrame::getFrameContent() {
	return fmessage;
}

/**
 *  adds to messages a Http frame and extracts the needed information from the input.
 */
void LoginFrame::createFrame() {

	std::string command = "POST /login.jsp ";
	int index = fmessage.find(" ");
	std::string username = fmessage.substr(0, index);
	fmessage = fmessage.substr(index + 1);
	std::string phone;
		if(index>=0)
		 phone = fmessage;
		else phone=" ";

	fmessage = command;

	fmessage.append(http_VERSION + "\n\n");

	fmessage.append("UserName=" + enc.url_encode(username) + "&");
	fmessage.append("Phone=" + enc.url_encode(phone) + "\n");
}

LoginFrame::~LoginFrame() {
}



