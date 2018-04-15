/*
 * Utils.cpp
 *
 *  Created on: 15 de abr de 2018
 *      Author: vitor
 */

#include "Utils.h"

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}


char *Utils::concatValue(char *text, float value) {
	stringstream ss;
	ss << text;
	ss << value;
	string str = ss.str();

	const char *ret = str.c_str();
	int size = strlen(ret);

	char *retChar = (char *) calloc(sizeof(char), size);
	for (int i = 0; i < size; i++) {
		retChar[i] = ret[i];
	}

	return retChar;
}

char *Utils::concatChar(char *str1, char *str2) {
	char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
	strcpy(str3, str1);
	strcat(str3, str2);

	return str3;
}
