/*
 * WhatsappClient.hpp
 *
 *  Created on: Jan 11, 2015
 *      Author: ilanagre
 */

#ifndef WHATSAPPCLIENT_HPP_
#define WHATSAPPCLIENT_HPP_
//using namespace std;
#include <string>
#include "../include/ClientProtocol.h"
class WhatsappClient{
private:
	std::string fusername;
	std::string fphone;
	std::string fhost;
	unsigned short fport;
	std::string fuser_auth;
	bool fstop;
	const std::string fCommandToStop;

	void userInputListener();
	void networkInputListener();
	void sendQueue();
public:

	WhatsappClient(std::string host,std::string port,std::string initString);
	~WhatsappClient();
	void connect(std::string& initString);

};


#endif /* WHATSAPPCLIENT_HPP_ */
