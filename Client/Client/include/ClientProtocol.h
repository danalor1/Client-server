/*
 * ClientProtocol.hpp
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */

#ifndef CLIENTPROTOCOL_HPP_
#define CLIENTPROTOCOL_HPP_
#include "../include/ConnectionHandler.h"
#include "../include/HttpFrame.h"

class ClientProtocol {

private:
	ClientProtocol(std::string host, short port, std::string username,std::string phone,std::string cookie);
	//copy constructor and operator= are private to support singleton pattern.
	ClientProtocol(ClientProtocol const&);
	ClientProtocol& operator=(ClientProtocol const&);
	//the only instance of the protocol.
	static ClientProtocol* instance;
	static bool bitchplease;
	//connection handler to send and recieve massages over TCP.
	ConnectionHandler fconnectionHandler;
	bool isConnected;
	//holds the username of the current client.
	bool isLoggedIn;
	std::string fusername;
	std::string fphone;
	void updateCookie(std::string header);

	//unique identifier for each subscription.
	std::string fcookie;



	//checks whether current client is subscribed to given client name.
	bool isFollowing(std::string username);
	//returns the index of the given client of -1 if current client is not subscribed to it.
	int getUserIndex(std::string username);
	//the type of argument of this function is decided at runtime.
	 bool sendFrameString(HttpFrame * frame);
	//all possible client commands.



	enum commands {
		LOGIN = 0,
		LOGOUT= 1,
		LIST = 2,
		CREATEGROUP = 3,
		SEND = 4,
		ADDUSER = 5,
		REMOVEUSER = 6,
		QUEUE = 7,
		UNKNOWN_COMMAND=8,
		WELCOME=9,
		MESSAGE=10,
		ERROR=11,
		STOP=12,
		EXIT=13
	};




	commands command(std::string command);

	const std::string TERMINATE_COMMAND;

public:
	 ~ClientProtocol();
	//processes commands recieved from the console.
	std::string processUserCommand(std::string message);
	//processes frames recieved from the network.
	std::string processRecievedFrame(std::string message);
	//listens to incomming message.
	std::string listen();
	bool isConnect(){
		return isConnected;
	}
	//returns the only instance of the protocol.
	static ClientProtocol * createInstance(std::string host, short port, std::string username,std::string phone,std::string user_auth);
	static ClientProtocol * getInstance();

};



#endif /* CLIENTPROTOCOL_HPP_ */
