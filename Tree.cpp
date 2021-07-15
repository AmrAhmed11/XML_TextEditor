#include "types.h"

string strmin = "";
string strprt = "";

using namespace std;

Tree::Tree(Node* r)
{
    root = r;
}

Tree::Tree(){
    root=NULL;
}

Tree::~Tree()
{
}

void Tree::setRoot(Node* r){
    root = r;
}

Node::Node(string v)
{
    value = v;
    parent = NULL;
    position = 0;
    type = 0;
}

Node::~Node()
{
}

void Node::setParent(Node* p) {
    parent = p;
}

void Node::setAttributes(string a) {
    attributes = a;
}

void Node::setData(string d) {
    data = data + d;
}

Node* Node::insertChild(string p) {
    Node* n = new Node(p);
    n->setParent(this);
    children.push_back(n);
    return n;
}

Node* Node::getParent() {
    return parent;
}

int Node::getType() {
    return type;
}

string Node::getData() {
    return data;
}

string Node::getValue() {
    return value;
}

int Node::getPosition() {
    return position;
}

void Node::setType(int t) {
    type = t;
}

vector<Node*> Node::getChildren() {
    return children;
}

string Node::getAttributes() {
    return attributes;
}

void Tree::print(Node* r) {
    vector<Node*> children = r->getChildren();
    for (int i = 0; i < children.size(); i++) {
        print(children[i]);
    }
    cout << "Value = " << r->getValue() << " & " << "Data = " << r->getData() << " & " << "attr = " << r->getAttributes() << endl;
}

void Tree::minifyNode(Node* r) {
    if (r->getType() == 0) { //normal open-close tags

        strmin += "<" + r->getValue();

        if (!r->getAttributes().empty()) {
            strmin += " " + r->getAttributes();
        }
        strmin+=">"+r->getData();
        for (int i = 0; i < r->getChildren().size(); i++) {
            minifyNode(r->getChildren()[i]);
        }
        strmin+="</"+r->getValue()+">";
    }
    else if (r->getType() == 1) {  //self-closing tags
        //  <frame f_num="2"/>
        strmin+="<"+r->getValue();
        if (!r->getAttributes().empty()) {
            strmin+=" "+r->getAttributes();
        }
        strmin+=">";
    }
    else if (r->getType() == 2) {
        //<!--A random selection of elements from data.xml
        //    Some IDREFS(refs attribute of element pointer) do not have a corresponding id in this sample-->
        strmin+="<"+r->getAttributes()+">";
    }
    else if (r->getType() == 3) {
        for (int i = 0; i < r->getChildren().size(); i++) {
            minifyNode(r->getChildren()[i]);
        }
    }
    else if (r->getType() == 4) {
        strmin+="<"+r->getValue();
        if (!r->getAttributes().empty()) {
            strmin+=" "+r->getAttributes();
        }
        strmin+=">";
    }
}

void Tree::prettifyNode(Node* r, int h) {
    if(h==-1){
        strprt ="";
    }
    if (r->getType() == 0) { //normal open-close tags
        for (int i = 0; i < h; i++) {
            strprt+="    ";
        }
        strprt +="<"+r->getValue();
        if (!r->getAttributes().empty()) {
            strprt+=" "+r->getAttributes();
        }
        strprt+=">\n";
        if (r->getData() != "") {
            for (int i = 0; i < h + 1; i++) {
                strprt+="    ";
            }
            strprt+=r->getData()+"\n";
        }
        for (int i = 0; i < r->getChildren().size(); i++) {
            prettifyNode(r->getChildren()[i], h + 1);
        }

        for (int i = 0; i < h; i++) {
            strprt+="    ";
        }
        strprt += "</"+r->getValue()+">\n";
    }
    else if (r->getType() == 1) {  //self-closing tags
        //  <frame f_num="2"/>
        for (int i = 0; i < h; i++) {
            strprt+="    ";
        }
        strprt+="<"+r->getValue();
        if (!r->getAttributes().empty()) {
            strprt+=" "+r->getAttributes();
        }
        strprt+=">\n";
    }
    else if (r->getType() == 2) {
        //<!--A random selection of elements from data.xml
        //    Some IDREFS(refs attribute of element pointer) do not have a corresponding id in this sample-->
        for (int i = 0; i < h; i++) {
            strprt+="    ";
        }
        strprt += "<"+r->getAttributes()+">\n";
    }
    else if (r->getType() == 3) {
        for (int i = 0; i < r->getChildren().size(); i++) {
            prettifyNode(r->getChildren()[i], h + 1);
        }
    }
    else if (r->getType() == 4) {
        strprt+="<"+r->getValue();
        if (!r->getAttributes().empty()) {
            strprt+=" "+r->getAttributes();
        }
        strprt+=">\n";
    }
}

void Node::setPostion(int p){
    position = p;
}

string Tree::prettify(){
    strprt.clear();
    prettifyNode(root,-1);
    return strprt;
}

string Tree::minify(){
    strmin.clear();
    minifyNode(root);
    return strmin;
}

void Tree::jsonify(Node* r) {


}
