/*
 * LogoutFrame.h
 *
 *  Created on: Jan 14, 2015
 *      Author: radodani
 */

#ifndef LOGOUTFRAME_H_
#define LOGOUTFRAME_H_



#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"


class LogoutFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	LogoutFrame(std::string cookie);

	~LogoutFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};






#endif /* LOGOUTFRAME_H_ */
