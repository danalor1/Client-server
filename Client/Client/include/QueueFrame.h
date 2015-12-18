/*
 * QueueFrame.h
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */

#ifndef QUEUEFRAME_H_
#define QUEUEFRAME_H_

#include <string>
#include "../include/HttpFrame.h"
#include "../include/Encoder.h"



class QueueFrame: public HttpFrame {

private:
	const std::string http_VERSION="HTTP/1.1" ;
	void createFrame();
	Encoder enc=Encoder();

public:
	QueueFrame();
	QueueFrame(std::string cookie);
	~QueueFrame();
	//implementation of abstract method.
	std::string& getFrameContent();
};


#endif /* QUEUEFRAME_H_ */
