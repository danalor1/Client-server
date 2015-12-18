/*
 * loginFrame.h
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */

#ifndef LOGINFRAME_H_
#define LOGINFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class LoginFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	LoginFrame();
	LoginFrame(std::string message);
	~LoginFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};





#endif /* LOGINFRAME_H_ */
