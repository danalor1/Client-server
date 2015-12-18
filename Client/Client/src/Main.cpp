/*
 * Main.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: ilanagre
 */

#include "../include/LoginFrame.h"
#include "../include/WhatsappClient.h"
#include "../include/ConnectionHandler.h"

#include<string>

#include<iostream>
#include <stdlib.h>
#include <boost/locale.hpp>
#include "../include/Encoder.h"
int main (int argc, char *argv[]) {

	std::cout<<"Welcome to WhatsApp!if you want to stare go ahead, otherwise login to continue:"<< std::endl<< std::endl;
	std::string input;
	std::getline(std::cin,input);

	 std::string host=std::string(argv[1]);
	 std::string port=std::string(argv[2]);
	WhatsappClient whatClient=WhatsappClient(host,port,input);
	whatClient.connect(input);




}







