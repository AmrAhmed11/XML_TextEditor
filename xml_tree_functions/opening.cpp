#include "opening.h"

using namespace std;

void setData(string d){
    currentNode->setData(d);
}

void setAttribute(string s,int type){
    currentNode->setAttributes(s);
    currentNode->setType(type);
}

Error opening(string s , int index){
    //cout << s << "   ";
    //cout << currentNode->getValue() << " and data = " << currentNode->getData() << endl;
    //cout << currentNode->getData().empty() << endl;
    if(currentNode->getData().empty()){
            currentNode = currentNode->insertChild(s);
            //cout << endl;
            //cout << currentNode->getValue() << endl;
            //cout << endl;
            Error e ;
            e.type =0;
            //cout << currentNode->getValue()<< " = " <<currentNode->getData()<<endl;
            //cout <<"is right" << endl;
            return e;
    }
    else{
        Error e ;
        e.type =1;
        e.openPosition = index;
        //cout << currentNode->getValue() << " = " << currentNode->getData() << endl;
        //cout << "is wrong" << endl;
        return e;
    }

}