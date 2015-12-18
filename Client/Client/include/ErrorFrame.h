/*
 * ErrorFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef ERRORFRAME_H_
#define ERRORFRAME_H_

#include <string>
#include "../include/HttpFrame.h"


class ErrorFrame: public HttpFrame {

private:

	void createFrame();

public:
	ErrorFrame();
	ErrorFrame(std::string message);
	~ErrorFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};




#endif /* ERRORFRAME_H_ */
