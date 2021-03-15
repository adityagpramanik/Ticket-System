#include "fstream"
#include "seq.h"

using namespace std;

class Database {
    string username, password;

    public: 
    Database (): username(""), password("") {}
    Database (string _username, string _password): username(_username), password(_password) {}
    ~Database() {}
};

int main () {
    fstream data("index.dat", ios::out | ios::binary);
    string uname, pass ;

    cout<<"Create a username: ";
    cin>>uname;

    cout<<"Create a password: ";
    cin>>pass;

    Encrypt e_username(uname), e_pass(pass);

    e_username.encryption();
    e_pass.encryption();

    Database t(e_username.getMssg(), e_pass.getMssg());

    if (data)
        data.write((char*) &t, sizeof(Database));
        
    data.close();
    return 0;
}