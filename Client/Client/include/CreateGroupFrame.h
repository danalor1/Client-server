/*
 * CreateGroupFrame.h
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */

#ifndef CREATEGROUPFRAME_H_
#define CREATEGROUPFRAME_H_


#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class CreateGroupFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	Encoder enc=Encoder();
	void createFrame();

public:
	CreateGroupFrame();
	CreateGroupFrame(std::string cookie,std::string message);
	~CreateGroupFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};

#endif /* CREATEGROUPFRAME_H_ */
