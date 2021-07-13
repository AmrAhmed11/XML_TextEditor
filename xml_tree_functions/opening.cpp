#include "../main.cpp"

using namespace std;

void setData(string d){
    currentNode->setData(d);
}

void setAttribute(string s,int type){
    currentNode->setAttributes(s);
    currentNode->setType(type);
}

Error opening(string s , int index){
    if(currentNode->getData() == ""){
            currentNode = currentNode->insertChild(s);
            Error e ;
            e.type =0;
            return e;
    }
    else{
        Error e ;
        e.type =1;
        e.openPosition = index;
        return e;
    }

}