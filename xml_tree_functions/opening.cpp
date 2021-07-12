#include "../main.cpp"

using namespace std;

void setData(string d){
    currentNode->setData(d);
}

void setAttribute(vector<string> s){
    currentNode->setAttributes(s);
}

void openning(string s , int start ,int end){
    currentNode = currentNode->insertChild(s);
}