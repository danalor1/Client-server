/*
 * ClientProtocol.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */


#include "../include/ClientProtocol.h"
#include "../include/LoginFrame.h"
#include "../include/LogoutFrame.h"
#include "../include/ListUsersFrame.h"
#include "../include/WelcomeFrame.h"
#include "../include/ErrorFrame.h"
#include "../include/MessageFrame.h"
#include "../include/CreateGroupFrame.h"
#include "../include/SendFrame.h"
#include "../include/AddUserFrame.h"
#include "../include/QueueFrame.h"
#include "../include/RemoveUserFrame.h"
#include <boost/thread.hpp>
#include "../include/ConnectionHandler.h"

#include <cstdlib>
#include <string>

ClientProtocol* ClientProtocol::instance = NULL;


ClientProtocol::ClientProtocol(std::string host, short port, std::string username, std::string phone,std::string cookie) :
		fconnectionHandler(host, port), isConnected(false), isLoggedIn(false), fusername(username),fphone(phone), fcookie(cookie), TERMINATE_COMMAND(
				"exit") {

	//try to connect
	if (fconnectionHandler.connect()) {
		isConnected = true;
	}
}

/**
 * Creates one instance of the protocol and returns it whenever needed.
 *
 */
ClientProtocol * ClientProtocol::createInstance(std::string host, short port, std::string username,std::string phone,std::string cookie) {
	if(instance==NULL)
		instance = new ClientProtocol(host, port, username,phone,cookie);
	return instance;
}
ClientProtocol * ClientProtocol::getInstance() {

	return instance;
}

/**
 * Processes input received from the user.
 */
std::string ClientProtocol::processUserCommand(std::string message) {

	std::string response;

	//Check whether socket is open and connected to a server.
	if (fconnectionHandler.isOpen() && isConnected) {
		//looks up for key words to determine which command is it
		int index=message.find(" ");
		std::string commandString = message.substr(0,index);
		message=message.substr(index+1);

		HttpFrame * frame;

		commands enumCommand = command(commandString);

		if (!isLoggedIn) {

			//If not logged in yet...
			if (enumCommand == LOGIN) {
				frame = new LoginFrame(message);

				//send CONNECT frame.

				if (!sendFrameString(frame)) {

					response = TERMINATE_COMMAND;
				}

			} else {
				response = "You are not logged in";
				return response;
			}
		} else {
			//If already logged in...
			switch (enumCommand) {
			case LOGIN: {
				response = "You are logged in already";
				break;
			}


			case LOGOUT: {
				//Send DISCONNECT frame.
				frame = new LogoutFrame(fcookie);
				if (!sendFrameString(frame)) {
					response = TERMINATE_COMMAND;
				}
				break;
			}
			case SEND: {
							//send SEND frame.
							frame = new SendFrame(fcookie,message);
							if (!sendFrameString(frame)) {
								response = TERMINATE_COMMAND;
							}
							break;
						}
			case LIST: {
							//send List frame.
							frame = new ListUsersFrame(fcookie,message);
							if (!sendFrameString(frame)) {
								response = TERMINATE_COMMAND;
							}
							break;
						}
			case CREATEGROUP: {
										//send Create Group frame.
										frame = new CreateGroupFrame(fcookie,message);
										if (!sendFrameString(frame)) {
											response = TERMINATE_COMMAND;
										}
										break;
									}
			case ADDUSER: {
										//send Add frame.
										frame = new AddUserFrame(fcookie,message);
										if (!sendFrameString(frame)) {
											response = TERMINATE_COMMAND;
										}
										break;
									}
			case REMOVEUSER: {
										//send Remove frame.
										frame = new RemoveUserFrame(fcookie,message);
										if (!sendFrameString(frame)) {
											response = TERMINATE_COMMAND;
										}
										break;
									}
			case QUEUE: {
										//send queue frame.
										frame = new QueueFrame(fcookie);
										if (!sendFrameString(frame)) {
											response = TERMINATE_COMMAND;
										}

										break;
									}
			case EXIT: {
												frame = new MessageFrame("exit");
												if (!sendFrameString(frame)) {
													response = TERMINATE_COMMAND;
												}

												break;
											}

			default: {
				response = "Invalid command.";
				break;
			}
			}
		//	delete (frame);
		}
	}
	return response;
}

/**
 * Processes the server's response.
 */

std::string ClientProtocol::processRecievedFrame(std::string message) {

	std::string response;
	std::string commandString = message.substr(0, message.find("\n\n"));


	HttpFrame * frame;
	commands enumCommand = command(commandString);
	message=message.substr(message.find("\n\n")+2);

	switch (enumCommand) {

	case WELCOME: {

		frame = new WelcomeFrame();
		isLoggedIn = true;
		response = frame->getFrameContent();
		instance->updateCookie(commandString);
		break;
	}

	case MESSAGE: {
		frame = new MessageFrame(message);
		response = frame->getFrameContent();
		if(response.find("Goodbye")<=response.length()){
			isLoggedIn=false;
			fcookie="";

		}


		break;
	}
	case ERROR: {
		frame = new ErrorFrame();
		response = frame->getFrameContent();
		break;
	}

	default: {
		std::string error = "Malformed Http frame received!";
		frame = new ErrorFrame();
		break;
	}
	}
	delete(frame);
	return response;
}

/**
 * waits for the server response.
 */

std::string ClientProtocol::listen() {

	if (isConnected && fconnectionHandler.isOpen()) {

		std::string response;
		if (!fconnectionHandler.getLine(response)) {
			return processRecievedFrame("error");
		}

		return processRecievedFrame(response);
	} else {
		return TERMINATE_COMMAND;
	}
	return "";
}




/**
 * sends the given frame to the server.
 */

bool ClientProtocol::sendFrameString(HttpFrame * frame) {
	if (!fconnectionHandler.sendLine(frame->getFrameContent())) {
		std::cerr << "Cannot connect to server!";
		return false;
	}
	return true;
}

/**
 * returns command according to key words.
 */

ClientProtocol::commands ClientProtocol::command(std::string command) {

     if (command.compare("Login")==0) {
		return LOGIN;
	}
     else if (command.compare("Logout")==0) {
		return LOGOUT;
	}
     else if (command.compare("List")==0) {
		return LIST;
	}
     else if (command.compare("CreateGroup")==0) {
		return CREATEGROUP;
	}
     else if (command.compare("Send")==0) {
		return SEND;
	}
     else if (command.compare("Add")==0) {
		return ADDUSER;
	}
     else if (command.compare("Remove")==0) {
		return REMOVEUSER;
	}
     else if (command.compare("exit")==0) {
     		return EXIT;
     	}
     else if (command.compare("queue")==0) {
		return QUEUE;

	}
	else if (command.find("Set-Cookie")<=command.length()) {
			return WELCOME;
	}
	else{
		if(command.find("HTTP/1.1 200")<=command.length()){
		return MESSAGE;
		}
		else if (command.find("HTTP/1.1")<=command.length())
			return ERROR;
else
		return UNKNOWN_COMMAND;
		}

}
/**
 * updates the cookie when welcome message received
 */
void ClientProtocol::updateCookie(std::string header){
int index=header.find("=");
header=header.substr(index+1);
fcookie=header;
}


ClientProtocol::~ClientProtocol() {
	delete (instance);
}



