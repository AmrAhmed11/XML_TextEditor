#include "types.h"

using namespace std;

Tree::Tree(Node* r)
{
    root = r;
}

Tree::~Tree()
{
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

void Tree::minify(Node* r) {
    if (r->getType() == 0) { //normal open-close tags
        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">";
        cout << r->getData();
        for (int i = 0; i < r->getChildren().size(); i++) {
            minify(r->getChildren()[i]);
        }
        cout << "</" << r->getValue() << ">";
    }
    else if (r->getType() == 1) {  //self-closing tags
        //  <frame f_num="2"/>

        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">";
    }
    else if (r->getType() == 2) {
        //<!--A random selection of elements from data.xml
        //    Some IDREFS(refs attribute of element pointer) do not have a corresponding id in this sample-->
        cout << "<" << r->getAttributes() << ">";
    }
    else if (r->getType() == 3) {
        for (int i = 0; i < r->getChildren().size(); i++) {
            minify(r->getChildren()[i]);
        }
    }
    else if (r->getType() == 4) {
        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">";
    }
}

void Tree::prettify(Node* r, int h) {
    if (r->getType() == 0) { //normal open-close tags
        for (int i = 0; i < h; i++) {
            cout << "\t";
        }

        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">\n";
        if (r->getData() != "") {
            for (int i = 0; i < h + 1; i++) {
                cout << "\t";
            }
            cout << r->getData() << "\n";
        }
        for (int i = 0; i < r->getChildren().size(); i++) {
            prettify(r->getChildren()[i], h + 1);
        }

        for (int i = 0; i < h; i++) {
            cout << "\t";
        }
        cout << "</" << r->getValue() << ">\n";
    }
    else if (r->getType() == 1) {  //self-closing tags
        //  <frame f_num="2"/>
        for (int i = 0; i < h; i++) {
            cout << "\t";
        }
        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">\n";
    }
    else if (r->getType() == 2) {
        //<!--A random selection of elements from data.xml
        //    Some IDREFS(refs attribute of element pointer) do not have a corresponding id in this sample-->
        for (int i = 0; i < h; i++) {
            cout << "\t";
        }
        cout << "<" << r->getAttributes() << ">\n";
    }
    else if (r->getType() == 3) {
        for (int i = 0; i < r->getChildren().size(); i++) {
            prettify(r->getChildren()[i], h + 1);
        }
    }
    else if (r->getType() == 4) {
        cout << "<" << r->getValue();
        if (!r->getAttributes().empty()) {
            cout << " " << r->getAttributes();
        }
        cout << ">\n";
    }
}

void Tree::jsonify(Node* r) {


}