#include "string_manipulate.h"
using namespace std;

string trim_extra_mid_spaces(string s) {
    string out = "";
    bool first_space = false;
    bool locked = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '"') {
            locked = !locked;
        }
        if (!locked) {
            if (s[i] == ' ' && first_space == false) {
                out += s[i];
                first_space = true;
            }
            else if (s[i] != ' ') {
                first_space = false;
                out += s[i];
            }
        }
        else {
            out += s[i];
        }
    }
    return out;
}




vector<Error> stringManipulate(string input) {
    vector<Error> e;
    Error rtn;
    int index = 0;
    int i;
    int len = input.length();
    string tagstr, tagendstr, datastr, attrstr;
    for (index = 0; index < len; index++) {
        if (input[index] == '<') {
            if (input[index + 1] != '/' && input[index + 1] != '!' && input[index + 1] != '?') {
                i=index;
                while(1){
                    if (isspace(input[i]) || input[i] == '>') {
                        i = i - index - 1;
                        tagstr = input.substr(index + 1, i);
                        tagstr = trim(tagstr);
                        rtn = opening(tagstr, index + 1);
                        if(rtn.type != 0){
                            rtn.closePosition = index;
                            e.push_back(rtn);
                        }
                        index += i + 1;
                        break;
                    }
                    i++;
                }
                //attributes and self closing tag
                if (input[index] == ' ') {
                    i =index;
                    while(1){
                        if (input[i] == '>') {
                            int selfclosing= i - 1;
                            i = i - index - 1;
                            attrstr = input.substr(index + 1, i);
                            attrstr = trim_extra_mid_spaces(attrstr);
                            attrstr = trim(attrstr);
                            // check if self closing
                            if (input[selfclosing] == '/')
                            {
                                setAttribute(attrstr, 1);
                                rtn = closing (tagstr);
                                if(rtn.type != 0){
                                    rtn.closePosition = index;
                                    e.push_back(rtn);
                                }
                                index += i + 1;
                                break;
                            }
                            setAttribute(attrstr, 0);
                            index += i + 1;
                            break;
                        }
                        i++;
                    }
                }
            }
            // closing tag 
            else if (input[index + 1] == '/') {
                i=index;
                while(1){
                    if (input[i] == '>') {
                        i = i - index - 1;
                        tagendstr = input.substr(index + 2, i - 1);
                        tagendstr = trim(tagendstr);
                        //function to finish node with sub value
                        rtn = closing(tagendstr);
                        if(rtn.type != 0){
                            rtn.closePosition = index;
                            e.push_back(rtn);
                        }
                        index += (i + 1);
                        break;
                    }
                    i++;
                }
            }
            //comments tag
            else if (input[index + 1] == '!') {
                opening("", index + 1);
                for (int i = index; i < index + 2200; i++) {
                    if (input[i] == '>') {
                        i = i - index;
                        datastr = input.substr(index + 1, i - 1);
                        //function to set data with sub value
                        datastr = trim(datastr);
                        setAttribute(datastr, 2);
                        closing("");
                        index += i;
                        break;
                    }
                }
            }
            //XML tag 
            else if (input[index + 1] == '?') {
                i=index;
                while(1){
                    if (isspace(input[i]) || input[i] == '>') {
                        i = i - index - 1;
                        tagstr = input.substr(index + 1, i);
                        tagstr = trim(tagstr);
                        rtn = opening(tagstr, index + 1);
                        if(rtn.type != 0){
                            rtn.closePosition = index;
                            e.push_back(rtn);
                        }
                        index += i + 1;
                        break;
                    }
                    i++;
                }
                if (input[index] == ' ') {
                    i = index;
                    while(1){
                        if (input[i] == '>') {
                            i = i - index - 1;
                            attrstr = input.substr(index + 1, i);
                            //function to set attr with sub value
                            attrstr = trim_extra_mid_spaces(attrstr);
                            attrstr = trim(attrstr);
                            setAttribute(attrstr, 4);
                            rtn = closing(tagstr);
                            if(rtn.type != 0){
                                rtn.closePosition = index;
                                e.push_back(rtn);
                            }
                            index += i + 1;
                            break;
                        }
                        i++;
                    }
                }
            }
        }
        else if (input[index] == '\n' || isspace(input[index])) { continue; }
        else {
            i=index;
            while(1){
                if (input[i] == '<') {
                    i = i - index - 1;
                    datastr = input.substr(index, i + 1);
                    datastr = trim(datastr);
                    setData(datastr);
                    index += i;
                    break;
                }
                i++;
            }
        }
    }
    //checkBalance();
    return e;
}
