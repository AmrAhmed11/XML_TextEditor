#include "types.h"

using namespace std;

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

vector<Node*> Node::getChildren() {
    return children;
}

void Tree::print(Node* r) {
    vector<Node*> children = r->getChildren();
    for (int i = 0; i < children.size(); i++) {
        print(children[i]);
    }
    cout << r->getValue() << endl;
}

