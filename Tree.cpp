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
    void setType(int t);
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
    type = 0;
}

Node::~Node()
{
}

void Node::setParent(Node* p){
    parent = p;
}

void Node::setAttributes(string a){
    attributes = a;
}

void Node::setData(string d){
    data = data + d;
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

void Node::setType(int t){
    type=t;
}

struct Error {
    int openPosition;
    int closePosition;
    int type;
};

