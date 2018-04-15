/*
 * Utils.h
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

class Utils {
public:
	Utils();
	virtual ~Utils();
	static char *concatValue(char *str, float value);
	static char *concatChar(char *str1, char *str2);
};

#endif /* UTILS_H_ */
