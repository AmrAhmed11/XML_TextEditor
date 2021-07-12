

int closing(string s) {
    if (s == currentNode.getValue()) {
        currentNode = *currentNode.getParent();
        return 0;
    }
    else if (s == currentNode.getParent()->getValue()) {
        int returnValue = currentNode.getPosition();
        currentNode = *currentNode.getParent()->getParent();
        return returnValue;
    }
    else {
        return currentNode.getPosition();
    }
}