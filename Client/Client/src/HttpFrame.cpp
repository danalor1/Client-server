/*
 * HttpFrame.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */
#include "../include/HttpFrame.h"


HttpFrame::HttpFrame() :
      fmessage("Basic Http Frame") {

}
std::string& HttpFrame::getFrameContent() {
	return fmessage;
}


HttpFrame::~HttpFrame() {
}
