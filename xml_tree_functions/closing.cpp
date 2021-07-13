

Error closing(string s) {
    if (s == currentNode->getValue()) {
        currentNode = currentNode->getParent();
        Error e;
        e.type = 0;
        return e;
    }
    else if (s == currentNode->getParent()->getValue()) {
        Error e;
        e.openPosition = currentNode->getPosition();
        e.type = 1;
        currentNode = currentNode->getParent()->getParent();
        return e;
    }
    else {
        Error e;
        e.openPosition = currentNode->getPosition();
        e.type = 2;
        return e;
    }
}