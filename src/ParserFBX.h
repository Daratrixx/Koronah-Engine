/* 
 * File:   ParserFBX.h
 * Author: ANTOINE
 *
 * Created on 3 avril 2017, 23:21
 */

#ifndef PARSERFBX_H
#define PARSERFBX_H

#include "Types.h"

union PrimitiveTypeData {
    Uint16 Y;
    Uint8 C;
    Sint32 I;
    float F;
    double D;
    Sint64 L;
    
    char* S;
    char* R;
};

struct PropertyFBX {
    char TypeCode;
    // data
    // I  : Primitive Type
    char* Data;
    // II : Primitive Array
    Uint32 ArrayLength;
    Uint32 Encoding;
    Uint32 CompressedLength;
    // III: Special Type
    Uint32 Length;
};

struct NodeFBX {
    Uint32 EndOffset;
    Uint32 NumProperties;
    Uint32 PropertyListLen;
    Uint8 NameLen;
    char* Name;
    
    std::vector<PropertyFBX> NestedNode;
    std::vector<NodeFBX> NestedNode;
    
    Uint8 NullRecord[13];
};

class FileFBX {
public:
    FileFBX(std::string path) {
        std::ifstream file(path.c_str(), std::ifstream::binary | std::ifstream::in);
        file.read(FileIntroductionSTR, 21);
        file.read((char*)UnknownBytes, 2);
        file.read((char*)Version, 4);
    }
    
    NodeFBX loadNode(std::ifstream & file) {
        NodeFBX out;
        
        return out;
    }
    
    PropertyFBX loadProperty(std::ifstream & file) {
        PropertyFBX out;
        
        return out;
    }
    
    
private:
    char* FileIntroductionSTR;
    Uint16 UnknownBytes;
    Uint32 Version;
    NodeFBX rootNode;
};

#endif /* PARSERFBX_H */

