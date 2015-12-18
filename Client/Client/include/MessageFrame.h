/*
 * MessageFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef MESSAGEFRAME_H_
#define MESSAGEFRAME_H_
#include <string>
#include "../include/HttpFrame.h"


class MessageFrame: public HttpFrame {

private:

	void createFrame();

public:
	MessageFrame();
	MessageFrame(std::string message);
	~MessageFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};


#endif /* MESSAGEFRAME_H_ */
