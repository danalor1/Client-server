/*
 * SendFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#include "../include/SendFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include<boost/tokenizer.hpp>



SendFrame::SendFrame()
		 {
	fmessage="";
}

SendFrame::SendFrame(std::string cookie,std::string message) {
	fcookie=cookie;
	 fmessage=message;
	createFrame();
}

/**
 * returns the frame content
 */
std::string& SendFrame::getFrameContent() {
	return fmessage;
}

/**
 *  adds to messages a Http frame and extracts the needed information from the input.
 */
void SendFrame::createFrame() {

	std::string command = "POST /send.jsp ";
	unsigned int index = fmessage.find(" ");
	std::string mssageType = fmessage.substr(0, index);
    if(mssageType.find("User")<=mssageType.length())mssageType="Direct";

	fmessage = fmessage.substr(index + 1);
	index = fmessage.find(" ");

		std::string target;
			if( index<=fmessage.length()){


			target = fmessage.substr(0, index);
			}
			else
				if(fmessage.length()!=0)target=fmessage;
				else
					target=" ";

		fmessage = fmessage.substr(index + 1);
		std::string content = fmessage;
	fmessage = command;
	fmessage.append( http_VERSION + "\n");
	fmessage.append("Cookie: user_auth="+fcookie+"\n\n");
	fmessage.append("Type=" + enc.url_encode(mssageType) + "&");
	fmessage.append("Target=" +enc.url_encode( target) + "&");
	fmessage.append("Content=" +enc.url_encode( content) + "\n");
}

SendFrame::~SendFrame() {
}



