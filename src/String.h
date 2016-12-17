/* 
 * File:   String.h
 * Author: ANTOINE
 *
 * Created on 15 février 2016, 15:46
 */
#pragma once

#ifndef STRING_H
#define	STRING_H

#ifndef TYPES_H
#include "Types.h"
#endif

float toFloat(std::string str);
int toInt(std::string str);
int toInt(char c);
std::string toString(int value);
std::string toString(float value, int length);
float expressionValue(std::string expr);
bool replace(std::string &str, std::string from, std::string to);
std::string inter(std::string str, std::string left,std:: string right);
std::string readUntil(std::string &str, std::string end);
/*
    - - String parser - -
    http://stackoverflow.com/questions/17073979/string-calculator-substr
    I hope there's no problems in me taking your piece of code, it was really helpful.

    - - String replace - -
    http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
    Same, this is really useful.
*/

#endif	/* STRING_H */

