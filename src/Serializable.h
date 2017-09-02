/* 
 * File:   Serializable.h
 * Author: ANTOINE
 *
 * Created on 15 février 2017, 18:01
 */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "Types.h"

class Serializable {
public:
    virtual bool saveToFile(std::string file);
    virtual bool toFile(std::ofstream & fout);
    virtual bool writeInFile(std::ofstream & fout);
    virtual bool loadFromFile(std::string file);
    virtual bool fromFile(std::ifstream & fin);
    virtual bool readFromFile(std::ifstream & fin);
};

#endif /* SERIALIZABLE_H */

