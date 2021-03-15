#include "fstream"
#include "iostream"

using namespace std;

class Database {
    string username, password;

    public: 
    void display () {
        cout<<"username: "<<this->username<<endl;
        cout<<"password: "<<this->password<<endl;
    }
    
    ~Database() {}
};

int main () {
    string str;
    fstream rfile ("index.dat", ios::in | ios::binary);
    Database t;

    while ( rfile.read((char*) &t, sizeof(t)) )
        t.display();

    rfile.close();
    return 0;
}