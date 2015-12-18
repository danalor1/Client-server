/*
 * ErrorFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */



#include "../include/ErrorFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>


ErrorFrame::ErrorFrame()
		{
	fmessage="";
	createFrame();
}

/**
 * returns the frame content
 */
std::string& ErrorFrame::getFrameContent() {
	return fmessage;
}

/**
 * writes an error message
 */
void ErrorFrame::createFrame() {
	fmessage = "There was an error in the string you entered,\n Try again!";
}

ErrorFrame::~ErrorFrame() {
}

