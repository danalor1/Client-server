/*
 * WelcomeFrame.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: radodani
 */




#include "../include/WelcomeFrame.h"
#include "../include/HttpFrame.h"
#include <cstdlib>
#include <string>
#include <iostream>


WelcomeFrame::WelcomeFrame()
		 {
	fmessage="";
	createFrame();
}

/**
 * returns the frame content
 */
std::string& WelcomeFrame::getFrameContent() {
	return fmessage;
}

/**
 * creates a confirmation message for login
 */
void WelcomeFrame::createFrame() {
	fmessage = "Logged in successfully!";
}

WelcomeFrame::~WelcomeFrame() {
}
