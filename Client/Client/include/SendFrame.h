/*
 * SendFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef SENDFRAME_H_
#define SENDFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"



class SendFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	SendFrame();
	SendFrame(std::string cookie,std::string message);
	~SendFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};



#endif /* SENDFRAME_H_ */
