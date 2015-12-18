/*
 * HttpFrame.h
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */

#ifndef HTTPFRAME_H_
#define HTTPFRAME_H_

#include <string>


class HttpFrame {

protected:
	std::string fmessage;
	std::string fcookie;





public:
	//Returns a string representation of the frame.
	HttpFrame();

	virtual std::string& getFrameContent();
	virtual ~HttpFrame();

};


#endif /* HTTPFRAME_H_ */
