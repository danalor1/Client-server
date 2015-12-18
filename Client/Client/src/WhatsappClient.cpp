/*
 * WhatsappClient.cpp

 *
 *  Created on: Jan 11, 2015
 *      Author: radodani
 */

#include <string>
#include <cstdlib>
#include <iostream>
//#include <socket.h>
#include <boost/thread.hpp>
#include "../include/WhatsappClient.h"
#include "../include/ConnectionHandler.h"
#include "../include/ClientProtocol.h"


WhatsappClient::WhatsappClient(std::string host,std::string port,std::string input): fusername(""),fphone(""),fhost(""),fport(0),fuser_auth(""),fstop(false),fCommandToStop("exit")
{

fhost=host;
fport = atoi(port.c_str());



}
void WhatsappClient::connect(std::string& initString) {
	ClientProtocol::createInstance(fhost, fport, fusername,fphone,fuser_auth)->processUserCommand(initString);
	//Start running threads.
	boost::thread userInputThread(boost::bind(&WhatsappClient::userInputListener, this));
	boost::thread networkInputThread(boost::bind(&WhatsappClient::networkInputListener, this));
	boost::thread queueThread(boost::bind(&WhatsappClient::sendQueue, this));



	//Wait until all threads are done before exiting.
	queueThread.join();
	userInputThread.join();
	networkInputThread.join();

}
void WhatsappClient::userInputListener() {

	std::string response;
	const short bufsize = 1024;
	char buf[bufsize];
	while (!fstop) {
		//wait for input from user.
		std::cin.getline(buf, bufsize);
		std::string line(buf);
		if (line.find("exit")<=line.length()){
							std::cout<<"Sent exit request"<<std:: endl;
							 boost::this_thread::sleep( boost::posix_time::seconds(2) );
									fstop = true;
						}


		response = ClientProtocol::createInstance(fhost, fport, fusername,fphone,fuser_auth)->processUserCommand(line);


			std::cout << response << std::endl;


		}

}
void WhatsappClient::sendQueue() {


	//While termination request not recieved.
	while (!fstop) {
		 ClientProtocol::createInstance(fhost, fport, fusername,fphone,fuser_auth)->processUserCommand("queue");
		 boost::this_thread::sleep( boost::posix_time::seconds(2) );
		}


}

/**
 * Listens to input from the server.
 */
void WhatsappClient::networkInputListener() {
	std::string response;
	while (!fstop) {
		//Process sent message and get response.

		response = ClientProtocol::createInstance(fhost, fport, fusername,fphone,fuser_auth)->listen();
			//print out processed response.
		if (response.find("Exit")<=response.length()){
					std::cout<<"App is Closing Goodbye :)"<<std:: endl;
					 boost::this_thread::sleep( boost::posix_time::seconds(2) );
							fstop = true;
				}
        std::cout << response << std::endl;



	}

}
WhatsappClient::~WhatsappClient()
{



}

