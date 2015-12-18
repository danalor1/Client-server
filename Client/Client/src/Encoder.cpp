/*
 * Encoder.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */
#include "../include/Encoder.h"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>
Encoder::Encoder(){}

std::string Encoder::url_encode(const std::string &value) {
	std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
    	std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << '%' << std::setw(2) << int((unsigned char) c);
    }

    return escaped.str();
}

std::string Encoder::url_decode(std::string &SRC) {
	std::string ret;
    char ch;
    unsigned long int i;
    int ii;
    for (i=0; i<SRC.length(); i++) {
        if (int(SRC[i])==37) {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}
Encoder::~Encoder(){}

