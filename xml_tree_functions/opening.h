#ifndef OPENING_H
#define OPENING_H

#include "types.h"

extern Node* currentNode;

void setData(string d);
void setAttribute(string s, int type);
Error opening(string s, int index);

#endif // !OPENING_H

