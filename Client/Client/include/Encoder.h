/*
 * Encoder.h
 *
 *  Created on: Jan 13, 2015
 *      Author: radodani
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>



class Encoder {
private:

public:
Encoder();
std::string url_encode(const std::string &value);

std::string url_decode(std::string &SRC);
~Encoder();

 };


#endif /* ENCODER_H_ */
