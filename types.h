#ifndef TREE_CPP
#define TREE_CPP

#include <vector>
#include <QString>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

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
                //3
                //4 xml tag

public:
    Node(string v);
    void setParent(Node* p);
    void setAttributes(string a);
    void setData(string d);
    void setPostion(int p);
    string getData();
    string getValue();
    int getPosition();
    int getType();
    Node* getParent();
    string getAttributes();
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
    Tree();
    void setRoot(Node* r);
    void print(Node* r);
    void minifyNode(Node* r);
    void prettifyNode(Node* r, int h);
    string prettify();
    string minify();
    void jsonify(Node* r);
    ~Tree();
};


#endif // !TREE_H

