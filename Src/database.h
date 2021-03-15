#ifndef DATABASE_H
#define DATABASE_H

#include "iostream"
#include "iomanip"
#include "vector"

using namespace std;

class Database {
    string username, password, name, mob, email;

    public: 
    Database (): username(""), password(""), name(""), mob(""), email("") {}
    Database (string _username, string _password, string _name, string _mob, string _email):
            username(_username), password(_password), name(_name), mob(_mob), email(_email) {}
    
    string getPass () {
        return this->password;
    }

    string getUname () {
        return this->username;
    }

    ~Database() {}
};

#endif