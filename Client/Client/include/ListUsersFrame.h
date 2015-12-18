/*
 * ListUsersFrame.h
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */

#ifndef LISTUSERSFRAME_H_
#define LISTUSERSFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class ListUsersFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	ListUsersFrame();
	ListUsersFrame(std::string cookie,std::string message);
	~ListUsersFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};



#endif /* LISTUSERSFRAME_H_ */
