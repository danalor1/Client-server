/*
 * AddUserFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef ADDUSERFRAME_H_
#define ADDUSERFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class AddUserFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	Encoder enc=Encoder();
	void createFrame();

public:
	AddUserFrame();
	AddUserFrame(std::string cookie,std::string message);
	~AddUserFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};



#endif /* ADDUSERFRAME_H_ */
