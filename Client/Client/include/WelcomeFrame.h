/*
 * WelcomeFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef WELCOMEFRAME_H_
#define WELCOMEFRAME_H_

#include <string>
#include "../include/HttpFrame.h"


class WelcomeFrame: public HttpFrame {

private:

	void createFrame();

public:
	WelcomeFrame();
	WelcomeFrame(std::string cookie,std::string message);
	~WelcomeFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};



#endif /* WELCOMEFRAME_H_ */
