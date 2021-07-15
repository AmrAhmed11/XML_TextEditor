#include "closing.h"

using namespace std;

Error closing(string s) {
    //cout << s << "   ";
    //cout << currentNode->getValue();
    //cout << endl;
    if(currentNode->getType() == 3){
        Error e;
        e.type = 3;
        return e;
    }
    if (s == currentNode->getValue()) {
        currentNode = currentNode->getParent();
        Error e;
        e.type = 0;
        //cout << currentNode->getValue() <<endl;
        return e;
    }
    else if (s == currentNode->getParent()->getValue()) {
        Error e;
        e.openPosition = currentNode->getPosition();
        e.type = 1;
        currentNode = currentNode->getParent()->getParent();
        //cout << "CwrongERROR1" << endl;
        return e;
    }
    else {
        Error e;
        e.openPosition = currentNode->getPosition();
        e.type = 2;
        currentNode = currentNode->getParent();
        //cout << "CwrongERROR2" << endl;
        return e;
    }
}
