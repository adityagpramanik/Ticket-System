#include "invent.h"

using namespace std;

string Inventory::getName() {
    return this->movieName;
    }

vector <pair<string, bool>> Inventory::getShowTime() {
    return this->st;
    }
    
bool Inventory::getBlockBuster () {
    return this->bb;
    }