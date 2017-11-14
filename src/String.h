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

float toFloat(const std::string &  str);
Int toInt(const std::string &  str);
Int toInt(const char & c);
std::string toString(const Short & value);
std::string toString(const Int & value);
std::string toString(const Long & value);
std::string toString(const float & value, const UShort & length);
float expressionValue(const std::string & expr);
bool replace(std::string & str, const std::string & from, const std::string & to);
std::string inter(const std::string & str, const std::string & left, const std:: string & right);
std::string readUntil(std::string & str, const std::string & end);
std::string inParathesis(const std::string & in);

std::string getFileContentGLSL(std::string const & filePath);
std::string getGLSL(std::ifstream & fichier);
/*
    - - String parser - -
    http://stackoverflow.com/questions/17073979/string-calculator-substr
    I hope there's no problems in me taking your piece of code, it was really helpful.

    - - String replace - -
    http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
    Same, this is really useful.
*/

#endif	/* STRING_H */

