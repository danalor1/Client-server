/*
 * RemoveUserFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef REMOVEUSERFRAME_H_
#define REMOVEUSERFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class RemoveUserFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	RemoveUserFrame();
	RemoveUserFrame(std::string cookie,std::string message);
	~RemoveUserFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};




#endif /* REMOVEUSERFRAME_H_ */
