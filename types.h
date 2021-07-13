#ifndef TREE_CPP
#define TREE_CPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Error {
    int openPosition;
    int closePosition;
    int type;
};

class Node
{
private:
    string value;
    vector<Node*> children;
    Node* parent;
    int position;
    string attributes;
    string data;
    int type;   //0 open close
                //1 self close
                //2 comment

public:
    Node(string v);
    void setParent(Node* p);
    void setAttributes(string a);
    void setData(string d);
    string getData();
    string getValue();
    int getPosition();
    Node* getParent();
    vector<Node*> getChildren();
    void setType(int t);
    Node* insertChild(string p);
    ~Node();

};

class Tree
{
private:
    Node* root;
public:
    Tree(Node* r);
    void print(Node* r);
    ~Tree();
};


#endif // !TREE_H

