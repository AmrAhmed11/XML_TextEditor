#include <vector>
#include <string>

using namespace std;

class Node
{
private:
    string value;
    vector<Node*> children;
    Node* parent ;
    int position;   
    vector<string> attributes;
    string data;

public:
    Node(string v);
    void setParent(Node* p);
    void setAttributes(vector<string> a);
    void setData(string d);
    string getData();
    string getValue();
    int getPosition();
    Node* getParent();
    Node* insertChild(string p);
    ~Node();

};

class Tree
{
private:
    Node* root;
public:
    Tree( Node* r);
    ~Tree();
};

Tree::Tree(Node* r)
{
    root =r;
}

Tree::~Tree()
{
}



Node::Node(string v)
{
    value = v;
    parent  = NULL;
    position = 0;
}

Node::~Node()
{
}

void Node::setParent(Node* p){
    parent = p;
}

void Node::setAttributes(vector<string> a){
    attributes = a;
}

void Node::setData(string d){
    data = d;
}

Node* Node::insertChild(string p){
    Node* n = new Node(p);
    n->setParent(this);
    children.push_back(n);
    return n;
}

Node* Node::getParent() {
    return parent;
}

string Node::getData(){
    return data;
}

string Node::getValue() {
    return value;
}

int Node::getPosition(){
    return position;
}

struct Error {
    int openPosition;
    int closePosition;
    int type;
};