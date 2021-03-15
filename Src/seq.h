#ifndef SEQ_H
#define SEQ_H

#include "iostream"

class Encrypt {
    std::string mssg;

    public:
    Encrypt (std::string _mssg): mssg(_mssg) {}

    void encryption () {
        std::string temp{""};

        for (int i(0); i < this->mssg.size(); i++) {
            temp += this->mssg[i] + 3;
        }
        this->mssg = temp;
        temp.clear();
    }

    void decryption () {
        std::string temp("");

        for (int i(0); i < this->mssg.size(); i++) {
            temp += this->mssg[i] - 3;
        }
        this->mssg = temp;
        temp.clear();
    }

    std::string getMssg () {
        return this->mssg;
    }

    ~Encrypt() {}
};

#endif