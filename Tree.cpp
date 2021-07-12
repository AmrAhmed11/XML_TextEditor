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

public:
    Node(string v);
    void setParent(Node* p);
    void setAttributes(string a);
    void setData(string d);
    string getData();
    void insertChild(string p);
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
    attributes = "";
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
    data = d;
}

void Node::insertChild(string p){
    Node* n = new Node(p);
    n->setParent(this);
    children.push_back(n);
}

string Node::getData(){
    return data;
}