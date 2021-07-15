#include "balanced.h"

vector<Error> balanced(){
    vector<Error> e;
    Error toPush;
    while(currentNode->getType() != 3){
        toPush.openPosition = currentNode->getPosition();
        toPush.type = 1;
        e.push_back(toPush);
    }
    return e;
}
