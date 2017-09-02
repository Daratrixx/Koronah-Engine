#include "Serializable.h"

bool Serializable::saveToFile(std::string file) {
    std::ofstream fout;
    fout.open(file.c_str(), std::ios::binary | std::ios::out);
    if (!toFile(fout)) {
        fout.close();
        return false;
    }
    fout.close();
    return true;
}

bool Serializable::toFile(std::ofstream & fout) {
    return writeInFile(fout);
}

bool Serializable::writeInFile(std::ofstream & fout) {
    /*ULong addr = (unsigned)this;
    UInt size = sizeof(this);
    fout.write((char*) &addr, sizeof(unsigned));
    fout.write((char*) &size, sizeof(unsigned));
    fout.write((char*) this, size);*/
    return true;
}

bool Serializable::loadFromFile(std::string file) {
    std::ifstream fin;
    fin.open(file.c_str(), std::ios::binary | std::ios::in);
    if (!fromFile(fin)) {
        fin.close();
        return false;
    }
    fin.close();
    return true;
}

bool Serializable::fromFile(std::ifstream & fin) {
    return readFromFile(fin);
}

bool Serializable::readFromFile(std::ifstream & fin) {
    fin.read((char*) this, sizeof(this));
    return true;
}
